#ifndef RAND_HPP
#define RAND_HPP

#include "vec3.hpp"

// Generate a random float.
float randf();

// Random point in the unit sphere.
Vec3 rand_in_unit_sphere();

// Random point in a hemisphere.
Vec3 rand_in_hemisphere(const Vec3& normal);

#endif