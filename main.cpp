#include <stdio.h>
#include <stdlib.h>
#include "util/img.hpp"

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720

#define IMG_SIZE (IMG_WIDTH * IMG_HEIGHT * 3)

int main(int argc, char *argv[]) {
    printf("StingRay v0.0.0 [WRP]\n");

    unsigned char *pixels = (unsigned char *)malloc(IMG_SIZE);
    for (int i = 0; i < IMG_SIZE; i += 3) {
        pixels[i + 0] = 255;  // Red
        pixels[i + 1] = 0  ;  // Green
        pixels[i + 2] = 0  ;  // Blue
    }
    save_png("test.png", IMG_WIDTH, IMG_HEIGHT, pixels);

    return 0;
}