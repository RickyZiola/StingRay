#include "rand.hpp"

// TODO: faster RNG (no stdlib)
float randf() {
    return (float)rand() / (float)RAND_MAX;
}

Vec3 rand_in_unit_sphere() {
    Vec3 dir = Vec3(randf(), randf(), randf());
    while(dir.dot(dir) > 1) dir = Vec3(randf(), randf(), randf());
    return dir.normalize();
}

Vec3 rand_in_hemisphere(const Vec3& normal) {
    Vec3 in_unit_sphere = rand_in_unit_sphere();
    if (in_unit_sphere.dot(normal) > 0.0) {
        return in_unit_sphere;
    } else {
        return -in_unit_sphere;
    }
}