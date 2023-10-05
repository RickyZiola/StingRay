#include "rand.hpp"

unsigned int seed = 0;
float randf() {
    seed = (seed * 1664525u + 1013904223u) & 0xFFFFFFFFu;
    return ((float)(seed) / (float)0xFFFFFFFFu);
}
// TODO: (maybe) gaussian distribution for faster sphere generation.
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