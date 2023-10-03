#ifndef RAY_HPP
#define RAY_HPP

class Ray;
struct HitInfo;

#include "../util/vec3.hpp"
#include "../objects/object.hpp"

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

struct HitInfo {
    bool hit;
    Ray ray;

    float distance;
    Vec3 position;
    Vec3 normal;

    Object *object;
};

#endif