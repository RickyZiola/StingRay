#include <stdio.h>
#include <stdlib.h>
#include "renderer/buffer.hpp"
#include "renderer/renderer.hpp"

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720

int main(int argc, char *argv[]) {
    char *filename = (char *)"out.png";

    if (argc > 1) {
        filename = argv[1];
    }

    printf("StingRay v0.0.0 [WRP]\n");

    RenderBuffer img = RenderBuffer(IMG_WIDTH, IMG_HEIGHT);
    StingrayRenderer renderer = StingrayRenderer(img);

    renderer.render(0, 0, IMG_WIDTH - 1, IMG_HEIGHT - 1);


    img.save(filename);

    return 0;
}