#ifndef COLORMAT_HPP
#define COLORMAT_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"
#include "../util/rand.hpp"

/**
 * Simple diffuse material.
*/
class ColorMaterial : public Material {
private:
    Vec3 col;
public:
    /**
     * Create a new ColorMaterial
    */
    ColorMaterial(Vec3 col) {
        this->col = col;
    }

    /**
     * Return the color of the material
    */
    Vec3 color() { return this->col; }

    /**
     * Return the emission of the material (0.0 in this case)
    */
    Vec3 emission() { return Vec3(0.0); }

    /**
     * Scatter a ray on the material.
     * This is lambertian scattering.
    */
    Vec3 scatter(const Vec3& rayDir, const Vec3& norm) {
        return (norm + rand_in_unit_sphere()).normalize();
    }
};

#endif