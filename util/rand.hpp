#ifndef RAND_HPP
#define RAND_HPP

#include "vec3.hpp"

float randf() {
    return (float)rand() / (float)RAND_MAX;
}

Vec3 rand_in_unit_sphere() {
    return Vec3(randf(), randf(), randf()).normalize();
}

Vec3 rand_in_hemisphere(const Vec3& normal) {
    Vec3 in_unit_sphere = rand_in_unit_sphere();
    if (in_unit_sphere.dot(normal) > 0.0) {
        return in_unit_sphere;
    } else {
        return -in_unit_sphere;
    }
}

#endif