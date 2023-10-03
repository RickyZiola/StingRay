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

Vec3 StingrayRenderer::ray_shader(Ray& camera, Object *scene, int max_bounces) {
    HitInfo intersect = scene->intersect(camera);
    if (intersect.hit)
        return intersect.normal.dot(Vec3(3, 3, -3).normalize());
    return Vec3(fmaxf(0.0, fminf(1.0, powf(Vec3(3, 3, -3).normalize().dot(camera.direction), 15)))) * Vec3(.9, .9, .7) + Vec3(0.3, 0.4, 0.9);
}

void StingrayRenderer::render(int startX, int startY, int endX, int endY, int samples, Object *scene) {
    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            Vec3 uv = Vec3(
                (float)x / (float)this->buffer.width,
                (float)y / (float)this->buffer.height,
                0.0 );
            uv.x *= 2.0f;
            uv.y *= -2.0f;

            uv.x -= 1.0f;
            uv.y += 1.0f;

            uv.x *= (float)this->buffer.width / (float)this->buffer.height;
            Ray orig_camera = this->camera_ray(uv);
            Vec3 color = Vec3(0);

            for (int i = 0; i < samples; i++) {
                    // Antialiasing by offestting the eye position by a small amount
                    // TODO: faster random number generation
                Ray camera = Ray (orig_camera.origin + Vec3((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX) * 0.002, orig_camera.direction);
                color = color + ray_shader(camera, scene);
            }
            color = color / (float)samples;
            color = color.clamp(0.0f, 1.0f);

            this->buffer.set_pixel(x, y, (int)(color.x * 255.0), (int)(color.y * 255.0), (int)(color.z * 255.0));
        }
    }
}