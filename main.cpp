#include <stdio.h>
#include <stdlib.h>
#include "renderer/buffer.hpp"

#define IMG_WIDTH  256
#define IMG_HEIGHT 256

int main(int argc, char *argv[]) {
    char *filename = (char *)"out.png";

    if (argc > 1) {
        filename = argv[1];
    }

    printf("StingRay v0.0.0 [WRP]\n");

    RenderBuffer<IMG_WIDTH, IMG_HEIGHT> img = RenderBuffer<IMG_WIDTH, IMG_HEIGHT>();

    img.save(filename);

    return 0;
}