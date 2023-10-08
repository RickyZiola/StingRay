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
#include <time.h>

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720

#define MAX_THREADS 8

int main(int argc, char *argv[]) {

    printf("FrederickAmpsUp's StingRay Path tracer\n");

    RenderBuffer img          = RenderBuffer(IMG_WIDTH, IMG_HEIGHT);
    StingrayRenderer renderer = StingrayRenderer(img);
    StingrayDenoiser denoiser = StingrayDenoiser(img);

    EmissiveMaterial red   = EmissiveMaterial(Vec3(0.3, 0.0, 0.0));
    GlossyMaterial blue    = GlossyMaterial(  Vec3(0.3, 0.3, 0.8), 0.0);
    VolumeMaterial smoke   = VolumeMaterial(  Vec3(0.2, 0.7, 0.2));
    ColorMaterial white    = ColorMaterial(   Vec3(0.8, 0.8, 0.8));

    RefractiveMaterial glass = RefractiveMaterial(Vec3(1.0, 1.0, 1.0), 1.5, 0.1);

    VolumeMaterial dust = VolumeMaterial(Vec3(0.8, 0.8, 0.6));

    EmissiveMaterial light  = EmissiveMaterial(Vec3(0.9, 0.9, 0.8));

    StingrayScene *scene = new StingrayScene({
        new Sphere(Vec3(-0.5, -0.1, 1), 0.4,   &light),  // Emissive white sphere
        new Sphere(Vec3( 0.5, -0.1, 1.0), 0.4,   &blue),   // Glossy blue sphere
        new Sphere(Vec3( 1.5, 0, 1),  0.5,  &red),    // Glowing red sphere

        //new Volume(
        //    new Sphere(Vec3(), 200, NULL), &dust, 0.001 ),

        new Volume(
            new Sphere(Vec3( -1.5, 0, 1.0), 0.5, NULL), &smoke, 5.0),  // Dark smoky sphere
        
        new Sphere(Vec3( 0, .6, 1.0), 0.4, &glass),  // Glass ball
        new Sphere(Vec3( 0, -0.2, 0.5), 0.3, &glass),  // Glass ball infront of everything

        new Sphere(Vec3(0.0, -9999.5,  0.0), 9999.0, &white),  // Floor
        
        new Sphere(Vec3(0.0,   10000,  0.0), 9999.0, &white),  // Ceiling
        new Sphere(Vec3(-10001,  0.0,  0.0), 9999.0, &white),  // Left wall
        new Sphere(Vec3( 10001,  0.0,  0.0), 9999.0, &white),  // Right wall
        new Sphere(Vec3(0.0, 0.0,  10000.5), 9999.0, &white),  // Back wall
        new Sphere(Vec3(0.0, 0.0, -10000.5), 9999.0, &white)   // Front wall (behind the camera)
        
    });
    int id = time(NULL) & 0xffff;

    renderer.render(16, scene);
    printf("Rendering finished, denoising...\n");

    char *noisy_fname = (char *)malloc(17 + 4 + 1); // 17 bytes for "images/noisy-.png" + 4 bytes for ID + 1 byte for null terminator
    sprintf(noisy_fname, "images/noisy-%04x.png", id);

    img.save(noisy_fname);
    printf("Noisy image saved to %s\n", noisy_fname);
    free(noisy_fname);

    denoiser.denoise();

    char *denoised_fname = (char *)malloc(19 + 4 + 1); // 19 bytes for "images/denoised-.png" + 4 bytes for ID + 1 byte for null terminator
    sprintf(denoised_fname, "images/denoised-%04x.png", id);

    img.save(denoised_fname);
    printf("Denoised image saved to %s\n", denoised_fname);
    free(denoised_fname);

    return 0;
}