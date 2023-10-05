#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object;

#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"
class StingrayScene;

// Abstract base class for all objects
class Object {
public:
    virtual Material *mat() = 0;
    virtual HitInfo intersect(Ray& ray, StingrayScene *scene) = 0;
};

#endif