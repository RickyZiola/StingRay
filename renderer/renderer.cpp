#include "renderer.hpp"
#include "../util/vec3.hpp"
#include "../objects/sphere.hpp"
#include "../util/rand.hpp"
#include <cmath>
#include <stdio.h>

Ray StingrayRenderer::camera_ray(const Vec3& uv) {
    float FOV = .5 * 3.1415926535897932; // 90 degrees

    float angle_xz = (FOV / 2.0f) * uv.x;
    float angle_yz = (FOV / 2.0f) * uv.y;

    float loc_y = sin(angle_yz);
    float loc_x = sin(angle_xz);
    float loc_z = cos(angle_yz) * cos(angle_xz);

    Vec3 screen_plane = Vec3(loc_x, loc_y, loc_z).normalize();
    Vec3 eye = Vec3(0.0f); // Put the eye at the origin (for now)

    Vec3 direction = (screen_plane - eye).normalize();
    return Ray(eye, direction);
}

Vec3 StingrayRenderer::sky_color(const Vec3& dir) {
    return Vec3(fmaxf(0.0, fminf(1.0, powf(Vec3(3, 3, -3).normalize().dot(dir), 15)))) * Vec3(.9, .9, .7) + Vec3(0.3, 0.4, 0.9);
}

Vec3 StingrayRenderer::ray_shader(Ray camera, Object *scene, int max_bounces) {
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
        color = color * Vec3(0.8);

        camera.origin = intersect.position + intersect.normal * 0.0001f;
        camera.direction = rand_in_hemisphere(intersect.normal);
    }

    return light;
}

void StingrayRenderer::render(int startX, int startY, int endX, int endY, int samples, Object *scene) {
    int status_width = startX - endX / 8;
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

            uv.x *= (float)this->buffer.width / (float)this->buffer.height;
            Ray orig_camera = this->camera_ray(uv);
            Vec3 color = Vec3(0);

            for (int i = 0; i < samples; i++) {
                    // Antialiasing by offestting the eye position by a small amount
                    // TODO: faster random number generation
                Ray camera = Ray (orig_camera.origin + Vec3(randf(), randf(), randf()) * 0.002, orig_camera.direction);
                color = color + ray_shader(camera, scene);
            }
            color = color / (float)samples;
            color = color.clamp(0.0f, 1.0f);

            this->buffer.set_pixel(x, y, (int)(color.x * 255.0), (int)(color.y * 255.0), (int)(color.z * 255.0));
        }
    }
}