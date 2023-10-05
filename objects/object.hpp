#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object;

#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"
class StingrayScene;

// Abstract base class for all objects
class Object {
public:
    // Get the object's material
    virtual Material *mat() = 0;
    // Intersect a ray with the object
    virtual HitInfo intersect(Ray& ray, StingrayScene *scene) = 0;
};

#endif