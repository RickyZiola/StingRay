#ifndef RAY_HPP
#define RAY_HPP

#include "../util/vec3.hpp"

class Ray {
private:

public:
    Vec3 origin;
    Vec3 direction;

    Ray(Vec3 origin, Vec3 direction) {
        this->origin = origin;
        this->direction = direction;
    }
};

#endif