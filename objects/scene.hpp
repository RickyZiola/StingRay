#ifndef SCENE_HPP
#define SCENE_HPP

class StingrayScene;

#include "../renderer/ray.hpp"
#include "object.hpp"
#include <vector>

/**
 * Collection of objects.
 * This can be an object to make volumes with triangles.
*/
class StingrayScene : public Object {
private:
    std::vector<Object*> objects;

public:
    /**
     * Construct a new StingrayScene with the given objects.
    */
    StingrayScene(Object* objects[], int num_objects) {
        this->objects = std::vector<Object*>(num_objects);
        for (int i = 0; i < num_objects; ++i) {
            this->objects.push_back(objects[i]);
        }
    }

    /**
     * Copy a vector of objects.
    */
    StingrayScene(const std::vector<Object*>& objects) : objects(objects) { }

    /**
     * Intersect a ray with all objects in the scene, return the closest hit.
    */
    HitInfo intersect(Ray& r, StingrayScene *scene) {
        Object *closest = NULL;
        HitInfo closest_hit = HitInfo { false, &r, 0.0, Vec3(), Vec3(), NULL };
        float min_dist = 512; // Farclip
        for (int i = 0; i < objects.size(); ++i) {
            HitInfo hit = objects[i]->intersect(r, this);
            if (hit.hit && hit.distance < min_dist) {
                closest = objects[i];
                closest_hit = hit;
                min_dist = hit.distance;
            }
        }
        return closest_hit;
    }

    // Must be implemented to be an Object
    Material *mat() { return NULL; }

    void add(Object* object) {
        objects.push_back(object);
    }
};

#endif