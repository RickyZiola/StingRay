#ifndef OBJECT_HPP
#define OBJECT_HPP

class Object;

#include "../renderer/ray.hpp"

// Abstract base class for all objects
class Object {
public:
    virtual HitInfo intersect(const Ray& ray) = 0;
};

#endif