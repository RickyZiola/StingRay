#ifndef SCENE_HPP
#define SCENE_HPP

class StingrayScene;

#include "../renderer/ray.hpp"
#include "object.hpp"
#include <vector>

class StingrayScene {
private:
    std::vector<Object*> objects; // eww C++ style code

public:
    StingrayScene(Object* objects[], int num_objects) {
        this->objects = std::vector<Object*>(num_objects);
        for (int i = 0; i < num_objects; ++i) {
            this->objects.push_back(objects[i]);
        }
    }

    StingrayScene(const std::vector<Object*>& objects) : objects(objects) { }

    HitInfo intersect(Ray& r) {
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
};

#endif