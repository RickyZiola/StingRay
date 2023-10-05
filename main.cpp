#include <stdio.h>
#include <stdlib.h>
#include "objects/scene.hpp"
#include "renderer/buffer.hpp"
#include "renderer/renderer.hpp"
#include "renderer/denoiser.hpp"
#include "objects/colormat.hpp"
#include "objects/emissive.hpp"
#include "objects/glossy.hpp"
#include "objects/volume.hpp"
#include "objects/sphere.hpp"

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720

#define MAX_THREADS 8

int main(int argc, char *argv[]) {
    char *filename = (char *)"out.png";

    if (argc > 1) {
        filename = argv[1];
    }

    printf("StingRay v0.0.2\n");

    RenderBuffer img          = RenderBuffer(IMG_WIDTH, IMG_HEIGHT);
    StingrayRenderer renderer = StingrayRenderer(img);
    StingrayDenoiser denoiser = StingrayDenoiser(img);

    EmissiveMaterial red   = EmissiveMaterial(Vec3(0.3, 0.0, 0.0));
    GlossyMaterial blue    = GlossyMaterial(  Vec3(0.3, 0.3, 0.8), 0.3);
    ColorMaterial green    = ColorMaterial(   Vec3(0.0, 0.8, 0.0));
    ColorMaterial white    = ColorMaterial(   Vec3(0.8, 0.8, 0.8));


    VolumeMaterial dust = VolumeMaterial(Vec3(0.8, 0.8, 0.6));

    EmissiveMaterial light  = EmissiveMaterial(Vec3(0.9, 0.9, 0.8));

    StingrayScene *scene = new StingrayScene({
        new Sphere(Vec3(-0.5, 0, 1), 0.5,   &light),
        new Sphere(Vec3( 0.5, 0, 1), 0.5,   &blue),
        new Volume(
            new Sphere(Vec3(0.0, 0.0, 0.0), 200, NULL), &dust, 0.1),
        new Sphere(Vec3( 1.5, 0, 1),  0.5,  &red),
        new Sphere(Vec3( -1.5, 0, 1), 0.5,  &green),
        

        new Sphere(Vec3(0.0, -9999.5,  0.0), 9999.0, &white),
        new Sphere(Vec3(0.0,   10000,  0.0), 9999.0, &white),
        new Sphere(Vec3(-10001,  0.0,  0.0), 9999.0, &white),
        new Sphere(Vec3( 10001,  0.0,  0.0), 9999.0, &white),
        new Sphere(Vec3(0.0, 0.0,  10000.5), 9999.0, &white),
        new Sphere(Vec3(0.0, 0.0, -10000.5), 9999.0, &white)
    });

    renderer.render(16, scene);
    printf("Rendering finished, denoising...\n");
    denoiser.denoise();

    img.save(filename);

    return 0;
}