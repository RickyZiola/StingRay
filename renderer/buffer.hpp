#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../util/img.hpp"
#include <cstring>
#include <cstdlib>

class RenderBuffer {
private:
    int width;
    int height;
    unsigned char *buffer;

public:
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
        this->buffer[y * width * 3 + x * 3 + 1] = b;
    }
};

#endif