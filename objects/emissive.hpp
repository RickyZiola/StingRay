#ifndef EMISSIVE_HPP
#define EMISSIVE_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"

/**
 * Simple emissive material with a color.
*/
class EmissiveMaterial : public Material {
private:
    Vec3 col;
public:
    /**
     * Construct an emissive material.
    */
    EmissiveMaterial(Vec3 col) {
        this->col = col;
    }

    /**
     * Get the emission color.
    */
    Vec3 emission() { return this->col; }

    /**
     * Get the reflected color (0 for emissive).
    */
    Vec3 color() { return Vec3(0.0); }
    
    /**
     * Scatter a ray. This is arbitrary for this material.
    */
    Vec3 scatter(const Vec3& rayDir, const Vec3& norm) {
        return Vec3(1.0).normalize();
    }
};

#endif