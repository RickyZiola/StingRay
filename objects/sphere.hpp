#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "object.hpp"
#include "../util/vec3.hpp"
#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"
#include "scene.hpp"

class Sphere : public Object {
private:
    Vec3 center;
    float radius;
    Material *material;

public:
    Sphere(const Vec3& center, float radius, Material *mat) {
        this->center = center;
        this->radius = radius;
        this->material = mat;
    }

    // Thanks to https://raytracing.github.io/books/RayTracingInOneWeekend.html
    HitInfo intersect(Ray& r, StingrayScene *scene) {
        if ((r.origin - this->center).length() < this->radius) {
            Ray newRay = Ray(r.origin + r.direction * radius * 2.1, -r.direction);
            HitInfo intersect_info = this->intersect(newRay, scene);
            intersect_info.distance = (r.origin - intersect_info.position).length();
            return intersect_info;
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

    Material *mat() { return this->material; }
};

#endif