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

#include "../objects/object.hpp"

/**
 * Class to represent a ray.
*/
class Ray {
private:

public:
    Vec3 origin;
    Vec3 direction;
    bool viewRay;

    /**
     * Construct a new ray.
    */
    Ray(Vec3 origin, Vec3 direction, bool view) {
        this->origin = origin;
        this->direction = direction;
        this->viewRay = view;
    }
};


#endif