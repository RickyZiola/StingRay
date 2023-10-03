#include "renderer.hpp"
#include "../util/vec3.hpp"
#include "../objects/sphere.hpp"
#include <cmath>

Ray StingrayRenderer::camera_ray(const Vec3& uv) {
    Vec3 screen_plane = Vec3(uv.x, uv.y, 1.0f);
    Vec3 eye = Vec3(0.0f); // Put the eye at the origin

    Vec3 direction = (screen_plane - eye).normalize();
    return Ray(eye, direction);
}

Vec3 StingrayRenderer::ray_shader(Ray& camera, int max_bounces) {
    HitInfo intersect = Sphere(Vec3(0,0,1), 0.5).intersect(camera);
    if (intersect.hit)
        return intersect.normal;
    return Vec3(0,0,0);
}

void StingrayRenderer::render(int startX, int startY, int endX, int endY) {
    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            Vec3 uv = Vec3(
                (float)x / (float)this->buffer.width,
                (float)y / (float)this->buffer.height,
                0.0 );
            uv.x *= 2.0f;
            uv.y *= 2.0f;

            uv.x -= 1.0f;
            uv.y -= 1.0f;

            uv.y /= (float)this->buffer.width / (float)this->buffer.height;

            Ray camera = this->camera_ray(uv);

            Vec3 color = ray_shader(camera).abs();  // Avoid negative values, of course

            this->buffer.set_pixel(x, y, (int)(color.x * 255.0), (int)(color.y * 255.0), (int)(color.z * 255.0));
        }
    }
}