#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../util/vec3.hpp"


/*
 * TODO: scattering (brdf)
 */
class Material {
public:
    virtual Vec3 color() = 0;
};

#endif