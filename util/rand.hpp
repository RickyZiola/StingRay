#ifndef RAND_HPP
#define RAND_HPP

#include "vec3.hpp"

/**
 * Generates a random float between 0 and 1.
*/
float randf();

/**
 * Generates a random vector on the unit sphere.
*/
Vec3 rand_in_unit_sphere();

/**
 * Generates a random vector in the unit hemisphere definde by normal.
*/
Vec3 rand_in_hemisphere(const Vec3& normal);

#endif