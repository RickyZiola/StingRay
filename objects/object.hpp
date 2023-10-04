#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object;

#include "../renderer/ray.hpp"
#include "../renderer/material.hpp"

// Abstract base class for all objects
class Object {
public:
    virtual Material *mat() = 0;
    virtual HitInfo intersect(const Ray& ray) = 0;
};

#endif