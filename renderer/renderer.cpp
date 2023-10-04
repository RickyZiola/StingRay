#include "renderer.hpp"
#include "../util/vec3.hpp"
#include "../objects/sphere.hpp"
#include "../util/rand.hpp"
#include <cmath>
#include <stdio.h>

Ray StingrayRenderer::camera_ray(const Vec3& uv) {
    float FOV = 0.5 * 3.1415926535897932; // FOV in radians (set to 90deg)

    float angle_xz = (FOV / 2.0f) * uv.x;
    float angle_yz = (FOV / 2.0f) * uv.y;
    float loc_z = cos(angle_xz) * cos(angle_yz);

    Vec3 screen_plane = Vec3(uv.x, uv.y, loc_z);
    Vec3 eye = Vec3(0.0f, 0.0f, -1.0f);

    Vec3 direction = screen_plane.normalize();
    return Ray(eye, direction);
}

Vec3 StingrayRenderer::sky_color(const Vec3& dir) {
    return Vec3(fmaxf(0.0, fminf(1.0, powf(Vec3(3, 3, 3).normalize().dot(dir), 15)))) * Vec3(.9, .9, .7) + Vec3(0.3, 0.4, 0.9);
}

Vec3 StingrayRenderer::ray_shader(Ray camera, StingrayScene *scene, int max_bounces) {
    //return camera.direction.abs();
    HitInfo intersect = scene->intersect(camera);

    Vec3 color = Vec3(1.0f);
    Vec3 light = Vec3(0.0f);

    for (int bounce = 0; bounce < max_bounces; ++bounce) {
        HitInfo intersect = scene->intersect(camera); 
        if (!intersect.hit) {
            light = light + sky_color(camera.direction) * color;
            break;
        }
            // TODO: emission & color
        light = light + color * Vec3(0.0);
        color = color * intersect.object->mat()->color();

        camera.origin = intersect.position + intersect.normal * 0.0001f;
        camera.direction = intersect.object->mat()->scatter(camera.direction, intersect.normal);
    }

    return light;
}

void StingrayRenderer::render(int startX, int startY, int endX, int endY, int samples, StingrayScene *scene) {
    int status_width = (startX - endX) / 8;
    for (int x = startX; x <= endX; x++) {
        if (x % status_width == 0) this->buffer.save("_sray_prog.png");
        for (int y = startY; y <= endY; y++) {
            Vec3 uv = Vec3(
                (float)x / (float)this->buffer.width,
                (float)y / (float)this->buffer.height,
                0.0 );
            uv.x *= 2.0f;
            uv.y *= -2.0f;

            uv.x -= 1.0f;
            uv.y += 1.0f;

            uv.y *= (float)this->buffer.height / (float)this->buffer.width;
            Ray orig_camera = this->camera_ray(uv);
            Vec3 color = Vec3(0);

            for (int i = 0; i < samples; i++) {
                    // Antialiasing by offestting the eye position by a small amount
                    // TODO: faster random number generation
                Ray camera = Ray (orig_camera.origin + Vec3(randf(), randf(), randf()) * 0.002, orig_camera.direction);
                color = color + ray_shader(camera, scene);
            }
            color = color / (float)samples;

            // Gamma correct
            color.x = powf(color.x, 1.0/2.2);
            color.y = powf(color.y, 1.0/2.2);
            color.z = powf(color.z, 1.0/2.2);
            color = color.clamp(0.0, 1.0);

            this->buffer.set_pixel(x, y, (int)(color.x * 255.0), (int)(color.y * 255.0), (int)(color.z * 255.0));
        }
    }
}