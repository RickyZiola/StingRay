#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "buffer.hpp"
#include "ray.hpp"

class StingrayRenderer {
private:
    RenderBuffer &buffer;

    Ray camera_ray(const Vec3& uv);
    Vec3 ray_shader(Ray& camera, int max_bounces=5);

public:
    StingrayRenderer(RenderBuffer &buffer) : buffer(buffer) { };

    // Renders a portion of the image (in a rectangle)
    void render(int startX, int startY, int endX, int endY); 
};

#endif