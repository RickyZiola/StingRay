#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "../util/img.hpp"
#include <cstring>

template <int width, int height>
    class RenderBuffer {
    private:
        unsigned char buffer[width * height * 3];
    
    public:
        RenderBuffer() {
            this->clear();
        }

        void clear() {
            memset(buffer, 0, width * height * 3);
        }

        void save(const char *filename) {
            save_png(filename, width, height, buffer);
        }

        void set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
            this->buffer[y * width * 3 + x * 3 + 0] = r;
            this->buffer[y * width * 3 + x * 3 + 1] = g;
            this->buffer[y * width * 3 + x * 3 + 1] = b;
        }
    };

#endif