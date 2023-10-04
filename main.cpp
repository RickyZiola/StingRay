#include <stdio.h>
#include <stdlib.h>
#include "renderer/buffer.hpp"
#include "renderer/renderer.hpp"
#include "objects/scene.hpp"
#include "objects/colormat.hpp"

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720

int main(int argc, char *argv[]) {
    char *filename = (char *)"out.png";

    if (argc > 1) {
        filename = argv[1];
    }

    printf("StingRay v0.0.1 [WIP]\n");

    RenderBuffer img = RenderBuffer(IMG_WIDTH, IMG_HEIGHT);
    StingrayRenderer renderer = StingrayRenderer(img);

    ColorMaterial red   = ColorMaterial(Vec3(0.8, 0.0, 0.0));
    ColorMaterial green = ColorMaterial(Vec3(0.0, 0.8, 0.0));
    ColorMaterial blue  = ColorMaterial(Vec3(0.0, 0.0, 0.8));
    ColorMaterial white = ColorMaterial(Vec3(0.8, 0.8, 0.8));

    StingrayScene *scene = new StingrayScene({
        new Sphere(Vec3(-0.5, 0, 1), 0.5,           &white),
        new Sphere(Vec3( 0.5, 0, 1), 0.5,           &blue),
        new Sphere(Vec3(-1.5, 0, 1), 0.5,           &green),
        new Sphere(Vec3( 1.5, 0, 1), 0.5,           &red),
        new Sphere(Vec3(0.0, -9999.5, 0.0), 9999.0, &white)
    });

        // TODO: multithreading
    renderer.render(0, 0, IMG_WIDTH - 1, IMG_HEIGHT - 1, 8, scene);


    img.save(filename);

    return 0;
}