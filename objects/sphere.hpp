#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "../util/vec3.hpp"
#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"
#include "scene.hpp"

/**
 * Sphere class.
*/
class Sphere : public Object {
private:
    Vec3 center;
    float radius;
    Material *material;

public:
    /**
     * Create a new sphere with the given center, radius and material.
    */
    Sphere(const Vec3& center, float radius, Material *mat) {
        this->center = center;
        this->radius = radius;
        this->material = mat;
    }

    /**
     * Check if the given ray intersects the sphere.
     * If the ray is a view ray, the intersection point may be inside the sphere. If not, it must be on the surface.
    */
    // Thanks to https://raytracing.github.io/books/RayTracingInOneWeekend.html
    HitInfo intersect(Ray& r, StingrayScene *scene) {
        if (r.viewRay && (r.origin - this->center).length() < this->radius) {
            return HitInfo { true, &r, 0.0, r.origin, Vec3(0.57735026919), this };
        }

        Vec3 oc = r.origin - center;
        float a = r.direction.dot(r.direction);
        float half_b = oc.dot(r.direction);
        float c = oc.dot(oc) - radius*radius;
        float discriminant = half_b*half_b - a*c;

        if (discriminant < 0) {  // Miss
            return HitInfo { false, &r, 0.0, Vec3(), Vec3(), this };
        } else {                 // Hit
            float dist = (-half_b - sqrt(discriminant) ) / a;
            if (dist <= 0.0) return HitInfo { false, &r, 0.0, Vec3(), Vec3(), this };  // Miss, the object is behind the ray origin

            Vec3 pos = r.origin + r.direction * dist;
            Vec3 normal = (pos - center) / radius; // Fastest way to calculate normal

            return HitInfo { true, &r, dist, pos, normal, this };
        }
    }

    /**
     * Get the material of the sphere.
    */
    Material *mat() { return this->material; }
};

#endif