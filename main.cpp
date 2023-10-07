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
#include "objects/refractive.hpp"

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
    GlossyMaterial blue    = GlossyMaterial(  Vec3(0.3, 0.3, 0.8), 0.0);
    VolumeMaterial smoke   = VolumeMaterial(  Vec3(0.2, 0.7, 0.2));
    ColorMaterial white    = ColorMaterial(   Vec3(0.8, 0.8, 0.8));

    RefractiveMaterial glass = RefractiveMaterial(Vec3(1.0, 1.0, 1.0), 1.5, 0.2);

    VolumeMaterial dust = VolumeMaterial(Vec3(0.8, 0.8, 0.6));

    EmissiveMaterial light  = EmissiveMaterial(Vec3(0.9, 0.9, 0.8));

    StingrayScene *scene = new StingrayScene({
        new Sphere(Vec3(-0.5, -0.1, 1), 0.4,   &light),  // Emissive white sphere
        new Sphere(Vec3( 0.5, -0.1, 1.0), 0.4,   &blue),   // Glossy blue sphere
        new Sphere(Vec3( 1.5, 0, 1),  0.5,  &red),    // Glowing red sphere
        new Volume(
            new Sphere(Vec3( -1.5, 0, 1.0), 0.5, NULL), &smoke, 1.0),  // Dark smoky sphere
        
        new Sphere(Vec3( 0, .6, 1.0), 0.4, &glass),  // Glass ball

        new Sphere(Vec3(0.0, -9999.5,  0.0), 9999.0, &white),  // Floor
        
        new Sphere(Vec3(0.0,   10000,  0.0), 9999.0, &white),  // Ceiling
        new Sphere(Vec3(-10001,  0.0,  0.0), 9999.0, &white),  // Left wall
        new Sphere(Vec3( 10001,  0.0,  0.0), 9999.0, &white),  // Right wall
        new Sphere(Vec3(0.0, 0.0,  10000.5), 9999.0, &white),  // Back wall
        new Sphere(Vec3(0.0, 0.0, -10000.5), 9999.0, &white)   // Front wall (behind the camera)
        
    });



    renderer.render(128, scene);
    printf("Rendering finished, denoising...\n");
    denoiser.denoise();

    img.save(filename);

    return 0;
}