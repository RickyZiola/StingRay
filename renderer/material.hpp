#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../util/vec3.hpp"


/*
 * TODO: scattering (brdf)
 * texcoords
 */
class Material {
public:
    virtual Vec3 color() = 0;
    virtual Vec3 scatter(const Vec3& rayDir, const Vec3& norm) = 0;
};

#endif