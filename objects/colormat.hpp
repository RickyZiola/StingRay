#ifndef COLORMAT_HPP
#define COLORMAT_HPP

#include "../renderer/material.hpp"
#include "../util/vec3.hpp"

class ColorMaterial : public Material {
private:
    Vec3 col;
public:
    ColorMaterial(Vec3 col) {
        this->col = col;
    }

    Vec3 color() { return this->col; }
};

#endif