#ifndef COLORMAT_HPP
#define COLORMAT_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"
#include "../util/rand.hpp"

class ColorMaterial : public Material {
private:
    Vec3 col;
public:
    ColorMaterial(Vec3 col) {
        this->col = col;
    }

    Vec3 color() { return this->col; }
    Vec3 emission() { return Vec3(0.0); }
    
    Vec3 scatter(const Vec3& rayDir, const Vec3& norm) {
        return (norm + rand_in_unit_sphere()).normalize();
    }
};

#endif