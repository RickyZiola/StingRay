#include <stdio.h>
#include <stdlib.h>
#include "renderer/buffer.hpp"
#include "renderer/renderer.hpp"
#include "objects/scene.hpp"

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

    StingrayScene *scene = new StingrayScene({
        new Sphere(Vec3(0, 0, 1),   0.5),
        new Sphere(Vec3(0.5, 0, 1), 0.5),
    });

        // TODO: multithreading
    renderer.render(0, 0, IMG_WIDTH - 1, IMG_HEIGHT - 1, 32, scene);


    img.save(filename);

    return 0;
}