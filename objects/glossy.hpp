#ifndef GLOSSY_HPP
#define GLOSSY_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"
#include "../util/rand.hpp"

class GlossyMaterial : public Material {
private:
    Vec3 col;
    float roughness;
public:
    GlossyMaterial(Vec3 col, float roughness) {
        this->col = col;
        this->roughness = roughness;
    }

    Vec3 color() { return this->col; }
    Vec3 emission() { return Vec3(0.0); }
    
    Vec3 scatter(const Vec3& rayDir, const Vec3& norm) {
        return Vec3::mix(rayDir.reflect(norm), (norm + rand_in_unit_sphere()).normalize(), this->roughness);
    }
};

#endif