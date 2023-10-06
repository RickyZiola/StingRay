#ifndef EMISSIVE_HPP
#define EMISSIVE_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"
#include "../renderer/ray.hpp"

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
    Ray scatter(Ray& ray, const Vec3& norm) {
        return ray;
    }
};

#endif