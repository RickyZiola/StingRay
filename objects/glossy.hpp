#ifndef GLOSSY_HPP
#define GLOSSY_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"
#include "../util/rand.hpp"

/**
 * Glossy material with color and roughness.
*/
class GlossyMaterial : public Material {
private:
    Vec3 col;
    float roughness;
public:

    /**
     * Create a glossy material with the given color and roughness.
    */
    GlossyMaterial(Vec3 col, float roughness) {
        this->col = col;
        this->roughness = roughness;
    }

    /**
     * Get the color of the material.
    */
    Vec3 color() { return this->col; }

    /**
     * Get the emission of the material (0 for glossy / diffuse materials).
    */
    Vec3 emission() { return Vec3(0.0); }
    
    /**
     * Scatter a ray off the material. This mixed between a perfect reflection and a perfect diffuse.
    */
    Vec3 scatter(const Vec3& rayDir, const Vec3& norm) {
        return Vec3::mix(rayDir.reflect(norm), (norm + rand_in_unit_sphere()).normalize(), this->roughness);
    }
};

#endif