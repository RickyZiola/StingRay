#ifndef EMISSIVE_HPP
#define EMISSIVE_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"

class EmissiveMaterial : public Material {
private:
    Vec3 col;
public:
    EmissiveMaterial(Vec3 col) {
        this->col = col;
    }

    Vec3 emission() { return this->col; }
    Vec3 color() { return Vec3(0.0); }
    
    Vec3 scatter(const Vec3& rayDir, const Vec3& norm) {
        return Vec3(1.0).normalize();
    }
};

#endif