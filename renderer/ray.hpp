#ifndef RAY_HPP
#define RAY_HPP

class Ray;
class Object;

#include "../util/vec3.hpp"

/**
 * Struct to store ray hit information.
*/
struct HitInfo {
    bool hit;
    Ray *ray;

    float distance;
    Vec3 position;
    Vec3 normal;

    Object *object;
};

/**
 * Class to represent a ray.
*/
class Ray {
private:

public:
    Vec3 origin;
    Vec3 direction;
    int intMode;

    /**
     * Construct a new ray.
    */
    Ray(Vec3 origin, Vec3 direction, int intMode) {
        this->origin = origin;
        this->direction = direction;
        this->intMode = intMode;
    }
};


#endif