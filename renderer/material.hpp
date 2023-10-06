#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../util/vec3.hpp"
#include "ray.hpp"
/**
 * Base class for all materials.
*/
class Material {
public:
    // Get the material's color.
    virtual Vec3 color() = 0;
    // Get the material's emission.
    virtual Vec3 emission() = 0;
    // Scatter a ray off the material.
    virtual Ray scatter(Ray& ray, const Vec3& norm) = 0;
};

#endif