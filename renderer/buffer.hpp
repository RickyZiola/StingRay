#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../util/img.hpp"
#include "../util/vec3.hpp"
#include <cstring>
#include <cstdlib>

class RenderBuffer {
private:
    unsigned char *buffer;

public:
    int width;
    int height;

    RenderBuffer(int width, int height) {
        this->width  =  width;
        this->height = height;

        this->buffer = (unsigned char *)malloc(this->width * this->height * 3);
        this->clear();
    }

    ~RenderBuffer() {
        free(this->buffer);
    }

    void clear() {
        memset(buffer, 0, this->width * this->height * 3);
    }

    void save(const char *filename) {
        save_png(filename, this->width, this->height, buffer);
    }

    void set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
        this->buffer[y * width * 3 + x * 3 + 0] = r;
        this->buffer[y * width * 3 + x * 3 + 1] = g;
        this->buffer[y * width * 3 + x * 3 + 2] = b;
    }

    void set_pixel(int x, int y, Vec3 col) {
        col = col.clamp(0.0, 1.0);

        this->buffer[y * width * 3 + x * 3 + 0] = (int)(col.x * 255.0);
        this->buffer[y * width * 3 + x * 3 + 1] = (int)(col.y * 255.0);
        this->buffer[y * width * 3 + x * 3 + 2] = (int)(col.z * 255.0);
    }

    Vec3 get_pixel(int x, int y) {
        return Vec3(
            ((float)this->buffer[y * width * 3 + x * 3 + 0] / 255.0),
            ((float)this->buffer[y * width * 3 + x * 3 + 1] / 255.0),
            ((float)this->buffer[y * width * 3 + x * 3 + 2] / 255.0) );
    }

    unsigned char *get_buffer() {
        return this->buffer;
    }

    void cpy(RenderBuffer &other) {
        memcpy(this->buffer, other.buffer, this->width * this->height * 3);
    }
};

#endif