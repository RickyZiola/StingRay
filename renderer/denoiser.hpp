#ifndef DENOISER_HPP
#define DENOISER_HPP

#include "buffer.hpp"
#include "../util/vec3.hpp"
#include <stdio.h>

class StingrayDenoiser {
private:
    RenderBuffer& buf;

public:
    StingrayDenoiser(RenderBuffer& buf) : buf(buf) { }
    void denoise() {
        int texelSize = 10;
        int halfTexelSize = texelSize / 2;
        float sigma = 10.0f;
        RenderBuffer newBuf = RenderBuffer(this->buf.width, this->buf.height);

        for (int x = halfTexelSize; x < this->buf.width - halfTexelSize; ++x) {
            for (int y = halfTexelSize; y < this->buf.height - halfTexelSize; ++y) {
                Vec3 centerColor = this->buf.get_pixel(x,y);

                float brightness = 1.0;
                Vec3 color = centerColor;

                for (int oX = -halfTexelSize; oX < halfTexelSize; ++oX) {
                    for (int oY = -halfTexelSize; oY < halfTexelSize; ++oY) {
                        Vec3 col = this->buf.get_pixel(x+oX, y+oY);
                        float diff = (1 - (col - centerColor).length()) * expf(-(oX * oX + oY * oY) / (2 * sigma * sigma));
                        brightness += diff;
                        color = color + col * diff;
                    }
                }

                newBuf.set_pixel(x,y, (color / brightness).clamp(0.0, 1.0));
            }
        }
        
        this->buf.cpy(newBuf);
    }
};

#endif