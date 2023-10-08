#ifndef VOLUME_HPP
#define VOLUME_HPP

#include "object.hpp"
#include "../util/vec3.hpp"
#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"
#include "../util/rand.hpp"
#include "../renderer/material.hpp"
#include "emissive.hpp"
#include "scene.hpp"
#include <stdio.h>

/**
 * Material for volumes.
*/
class VolumeMaterial : public Material {
private:

public:
    Vec3 col;
    VolumeMaterial(const Vec3 &col) {
        this->col = col;
    }

    Vec3 emission() { return Vec3(0.0); }

    Vec3 color() {
        return col;
    }

    Ray scatter(Ray& ray, const Vec3& normal) {
        ray.direction = (ray.direction*0.125 + rand_in_unit_sphere() * (ray.direction + rand_in_unit_sphere()*0.5)).normalize();
        return ray;
    }
};

/**
 * A volume.
*/
class Volume : public Object {
private:
    Object *bounds;
    VolumeMaterial *material;
    float density;

public:
    /*
        * Create a new volume with the given bounds, material, and density.
        @param bounds the shape of the volume. Its material is unused, so should be NULL.
        @param mat the material of the volume. This must be or inherit from VolumeMaterial.
        @param density the density of the volume. This is in % scattered / unit through the volume, so 1 means 100% scattered through a 1 unit thick volume.
    */
    Volume(Object *bounds, VolumeMaterial *mat, float density) {
        this->bounds = bounds;
        this->material = mat;
        this->density = density;
    }

    /**
     * Intersect a ray with the volume.
    */
    HitInfo intersect(Ray& r, StingrayScene *scene) {
        if (r.intMode == 2) return HitInfo { false, &r, 0.0, Vec3(), Vec3(), this };
        HitInfo front_int = this->bounds->intersect(r, scene);
        if (!front_int.hit) {
            return front_int;
        }

        Ray back_ray = Ray(front_int.position + r.direction * .01, r.direction, 0);
        HitInfo scene_int = scene->intersect(back_ray, scene);
        back_ray.intMode = 2;
        HitInfo back_int = this->bounds->intersect(back_ray, scene);
        if (scene_int.hit && (scene_int.distance < back_int.distance)) back_int = scene_int;

        if (!back_int.hit) {
            return back_int;
        }

        float dist = (front_int.position - back_int.position).length();
        bool hit = randf() < (dist * density);

        // cursed, remove asap
        //this->material = (VolumeMaterial *)new EmissiveMaterial(Vec3(dist));
        //front_int.object = this;
        //return front_int;

        if (!hit) return HitInfo { false, &r, 0.0, Vec3(), Vec3(), this };

        Vec3 pos = front_int.position + r.direction * dist * randf();

        return HitInfo { true, &r, (pos - r.origin).length(), pos, Vec3(0.0, 0.0, 1.0), this };
    }

    /**
     * Get the material of the volume.
    */
    Material *mat() {
        return (Material *) this->material;
    }
};

#endif