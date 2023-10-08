#include "renderer.hpp"
#include "../util/vec3.hpp"
#include "../objects/sphere.hpp"
#include "../util/rand.hpp"
#include <cmath>
#include <stdio.h>

Ray StingrayRenderer::camera_ray(const Vec3& uv) {
    float FOV = 0.7 * 3.1415926535897932; // FOV in radians (set to 90deg)
    Vec3 eye = Vec3(0.0f, 0.0f, -1.0f);

    float angle_xz = (FOV / 2.0f) * uv.x;
    float angle_yz = (FOV / 2.0f) * uv.y;// - .1 * 3.1415926535897932;
    float loc_z = cos(angle_xz) * cos(angle_yz); // TODO: better camera that doesn't have fisheye distortion and can support FOV > 180

    Vec3 screen_plane = Vec3(sin(angle_xz), sin(angle_yz), loc_z);  // TODO: Depth of field

    Vec3 direction = screen_plane.normalize();
    return Ray(eye, direction, 0);
}

Vec3 StingrayRenderer::sky_color(const Vec3& dir) {
    return Vec3(fmaxf(0.0, fminf(1.0, powf(Vec3(3, 3, 3).normalize().dot(dir), 15)))) * Vec3(.9, .9, .7) + Vec3(0.3, 0.4, 0.9); /// Basic sun skybox
}

Vec3 StingrayRenderer::ray_shader(Ray camera, StingrayScene *scene, int max_bounces) {

    // Records of color and light along the ray path
    Vec3 color = Vec3(1.0f);
    Vec3 light = Vec3(0.0f);

    for (int bounce = 0; bounce < max_bounces; ++bounce) {
        // Get the intersection point with the scene
        HitInfo intersect = scene->intersect(camera, scene); 

        // If it missed, use the sky color.
        if (!intersect.hit) {
            light = light + sky_color(camera.direction) * color;
            break;
        }

        // Store the emission and color of the hit object
        light = light + color * intersect.object->mat()->emission();
        color = color * intersect.object->mat()->color();

        // If the color is black, no further steps will change the render, so leave the loop. This also breaks when the ray hits a light source (with no reflected light).
        if (color.length() < 0.001) break;

        camera.intMode = 0; // helps make glass easier to implement
        camera.origin = intersect.position;
        camera = intersect.object->mat()->scatter(camera, intersect.normal);  // Bounce the ray
    }

    return light;
}

void StingrayRenderer::render(int samples, StingrayScene *scene) {

    this->render(0,0, this->buffer.width - 1, this->buffer.height - 1, samples, scene);
}

void StingrayRenderer::render(int startX, int startY, int endX, int endY, int samples, StingrayScene *scene) {
    // Periodically save the image to show progress
    int status_rep_width = (endX - startX) / 32;

    // Iterate through each pixel in the specified area of the image
    for (int x = startX; x <= endX; x++) {
        if (x % status_rep_width == 0) {
            // Status reports
            this->buffer.save("_sray_prog.png");
            printf("%.2f%% done.\n", (float)(x - startX) / (float)(endX - startX) * 100.0);
        }
        for (int y = startY; y <= endY; y++) {
            // Calculate the UV coordinates
            Vec3 uv = Vec3(
                (float)x / (float)this->buffer.width,
                (float)y / (float)this->buffer.height,
                0.0 );
            uv.x *=  2.0f;
            uv.y *= -2.0f;

            uv.x -= 1.0f;
            uv.y += 1.0f;

            uv.y *= (float)this->buffer.height / (float)this->buffer.width;

            // UV is inverted on the Y because pixel coords start at the top left corner, and we want to start at the bottom left corner.
            // Aspect ratio correction is also applied.

            // Calculate the camera ray
            Ray orig_camera = this->camera_ray(uv);
            Vec3 color = Vec3(0);

            // Multiple samples
            for (int i = 0; i < samples; i++) {
                // Antialiasing by offestting the eye position by a small amount
                Ray camera = Ray (orig_camera.origin + Vec3(randf(), randf(), randf()) * 0.004, orig_camera.direction, true);
                // Run the ray through the scene. This is where all the work happens.
                color = color + ray_shader(camera, scene, 16);
            }
            // Average the samples
            color = color / (float)samples;

            // Gamma correct
            color.x = powf(color.x, 1.0/2.2);
            color.y = powf(color.y, 1.0/2.2);
            color.z = powf(color.z, 1.0/2.2);

            // No negative colors
            color = color.clamp(0.0, 1.0);

            // Write to the render buffer
            this->buffer.set_pixel(x, y, (int)(color.x * 255.0), (int)(color.y * 255.0), (int)(color.z * 255.0));
        }
    }
}