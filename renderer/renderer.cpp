#include "renderer.hpp"
#include "../util/vec3.hpp"
#include <cmath>

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

            Vec3 color = Vec3(
                fabs(uv.x), fabs(uv.y), fabs(uv.z) );

            this->buffer.set_pixel(x, y, (int)(color.x * 255.0), (int)(color.y * 255.0), (int)(color.z * 255.0));
        }
    }
}