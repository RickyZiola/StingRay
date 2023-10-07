#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "../util/vec3.hpp"
#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"
#include "scene.hpp"
#include <cstdio>

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


    // Thanks to https://raytracing.github.io/books/RayTracingInOneWeekend.html
    /**
     * Check if the given ray intersects the sphere.
     * If the ray is a view ray, the intersection point may be inside the sphere. If not, it must be on the surface.
    */
    HitInfo intersect(Ray& r, StingrayScene *scene) {
        Vec3 oc = r.origin - center;
        float Dococ = oc.dot(oc);
        if (Dococ < this->radius*this->radius) {
            if (r.intMode == 0) { // The intersection can be inside the sphere.
                return HitInfo { true, &r, 0.0, r.origin, Vec3(1,0,0), this };
            
            } else if (r.intMode == 2) { // We need the back intersection point.
                Ray newR = Ray(
                    r.origin + r.direction * (fabs(this->radius) * 2.01),
                    -r.direction,
                    r.intMode );
                return this->intersect(newR, scene);
            }
        }

        float a = r.direction.dot(r.direction);
        float half_b = oc.dot(r.direction);
        float c = Dococ - radius*radius;
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