#ifndef SCENE_HPP
#define SCENE_HPP

#include "object.hpp"
#include "sphere.hpp"
#include <vector>

class StingrayScene : public Object {
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

    HitInfo intersect(const Ray& r) {
        Object *closest = NULL;
        HitInfo closest_hit = HitInfo { false, r, 0.0, Vec3(), Vec3(), NULL };
        float min_dist = 512; // Farclip
        for (int i = 0; i < objects.size(); ++i) {
            HitInfo hit = objects[i]->intersect(r);
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