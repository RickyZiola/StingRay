#ifndef REFRACTIVE_HPP
#define REFRACTIVE_HPP

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
 * Material for refractives.
*/
class RefractiveMaterial : public Material {
private:

public:
    Vec3 col;
    float ior;
    float reflection;

    RefractiveMaterial(const Vec3 &col, float ior, float reflection) {
        this->col = col;
        this->ior = ior;
        this->reflection = reflection;
    }

    Vec3 color() { return col; }

    Vec3 emission() { return Vec3(0.0); }

    Ray scatter(Ray& ray, const Vec3& normal) {
        if (randf() < this->reflection * (1.0 - ray.direction.dot(normal))) {
            ray.origin = ray.origin + normal * 0.01;
            ray.direction = ray.direction.reflect(normal);
            return ray;
        } else {
            ray.intMode = 1;
            ray.origin = ray.origin - normal * 0.01;
            ray.direction = ray.direction.refract(normal, 1.0, this->ior);
            return ray;
        }
    }
};
#endif