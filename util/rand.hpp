#ifndef RAND_HPP
#define RAND_HPP

#include "vec3.hpp"

float randf();

Vec3 rand_in_unit_sphere();

Vec3 rand_in_hemisphere(const Vec3& normal);

#endif