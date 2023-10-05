#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../util/img.hpp"
#include "../util/vec3.hpp"
#include <cstring>
#include <cstdlib>

/**
 * Buffer class to hold images (24-bit RGB)
*/
class RenderBuffer {
private:
    unsigned char *buffer;

public:
    int width;
    int height;

    /**
     * Create an empty buffer with the given width and height
    */
    RenderBuffer(int width, int height) {
        this->width  =  width;
        this->height = height;

        this->buffer = (unsigned char *)malloc(this->width * this->height * 3);
        this->clear();
    }

    /**
     * Free the buffer memory
    */
    ~RenderBuffer() {
        free(this->buffer);
    }

    /**
     * Clear the buffer
    */
    void clear() {
        memset(buffer, 0, this->width * this->height * 3);
    }

    /**
     * Save the buffer to a PNG
    */
    void save(const char *filename) {
        save_png(filename, this->width, this->height, buffer);
    }

    /**
     * Set a pixel in the buffer to the given RGB
    */
    void set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
        this->buffer[y * width * 3 + x * 3 + 0] = r;
        this->buffer[y * width * 3 + x * 3 + 1] = g;
        this->buffer[y * width * 3 + x * 3 + 2] = b;
    }

    /**
     * Set a pixel in the buffer to the given RGB (in range (0,1])
    */
    void set_pixel(int x, int y, Vec3 col) {
        col = col.clamp(0.0, 1.0);

        this->buffer[y * width * 3 + x * 3 + 0] = (int)(col.x * 255.0);
        this->buffer[y * width * 3 + x * 3 + 1] = (int)(col.y * 255.0);
        this->buffer[y * width * 3 + x * 3 + 2] = (int)(col.z * 255.0);
    }

    /**
     * Get a pixel from the buffer
    */
    Vec3 get_pixel(int x, int y) {
        return Vec3(
            ((float)this->buffer[y * width * 3 + x * 3 + 0] / 255.0),
            ((float)this->buffer[y * width * 3 + x * 3 + 1] / 255.0),
            ((float)this->buffer[y * width * 3 + x * 3 + 2] / 255.0) );
    }

    /**
     * Get a handle to the raw buffer data
    */
    unsigned char *get_buffer() {
        return this->buffer;
    }

    /**
     * Copy another buffer
    */
    void cpy(RenderBuffer &other) {
        memcpy(this->buffer, other.buffer, this->width * this->height * 3);
    }
};

#endif