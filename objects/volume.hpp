#ifndef SPHERE_VOLUME_HPP
#define SPHERE_VOLUME_HPP

#include "object.hpp"
#include "../util/vec3.hpp"
#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"
#include "../util/rand.hpp"
#include "../renderer/material.hpp"
#include "emissive.hpp"
#include "scene.hpp"
#include <stdio.h>

class VolumeMaterial : public Material {
private:
    Vec3 col;

public:
    VolumeMaterial(const Vec3 &col) {
        this->col = col;
    }

    Vec3 emission() { return Vec3(0.0); }

    Vec3 color() {
        return col;
    }

    Vec3 scatter(const Vec3& rayDir, const Vec3& normal) {
        return rand_in_unit_sphere();
    }
};

class Volume : public Object {
private:
    Object *bounds;
    Material *material;
    float density;

public:
    /*
        @param bounds the shape of the volume. Its material is unused, so should be NULL.
        @param mat the material of the volume. This must be or inherit from VolumeMaterial.
        @param density the density of the volume. This is in % scattered / unit through the volume, so 1 means 100% scattered through a 1 unit thick volume.
    */
    Volume(Object *bounds, VolumeMaterial *mat, float density) {
        this->bounds = bounds;
        this->material = mat;
        this->density = density;
    }

    HitInfo intersect(Ray& r, StingrayScene *scene) {
        HitInfo front_int = this->bounds->intersect(r, scene);
        if (!front_int.hit) {
            return front_int;
        }

        Ray back_ray = Ray(front_int.position + r.direction *.01, r.direction, false);
        HitInfo back_int = scene->intersect(back_ray);
        if (!back_int.hit) {
            return back_int;
        }

        float dist = (front_int.position - back_int.position).length();
        bool hit = randf() < (dist * density);
        if (!hit) return HitInfo { false, &r, 0.0, Vec3(), Vec3(), this };

        Vec3 pos = front_int.position + r.direction * dist * randf();

        return HitInfo { true, &r, (pos - r.origin).length(), pos, Vec3(0.0, 0.0, 1.0), this };
    }

    Material *mat() {
        return (Material *) this->material;
    }
};

#endif