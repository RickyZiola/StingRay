#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <functional>
#include "renderer/buffer.hpp"
#include "renderer/renderer.hpp"
#include "renderer/denoiser.hpp"
#include "objects/scene.hpp"
#include "objects/colormat.hpp"
#include "objects/emissive.hpp"

#define IMG_WIDTH 1280
#define IMG_HEIGHT 720

#define MAX_THREADS 8

void render(int startX, int startY, int endX, int endY, int samples, StingrayScene *scene, int yoff, StingrayRenderer *renderer, int thread_id, int height) {
    renderer->render(startX, startY, endX, endY, samples, scene, thread_id, yoff, height);
}

int main(int argc, char *argv[]) {
    char *filename = (char *)"out.png";

    if (argc > 1) {
        filename = argv[1];
    }

    printf("StingRay v0.0.1 [WIP]\n");

    RenderBuffer img = RenderBuffer(IMG_WIDTH, IMG_HEIGHT);
    StingrayDenoiser denoiser = StingrayDenoiser(img);

    ColorMaterial red   = ColorMaterial(Vec3(0.8, 0.0, 0.0));
    ColorMaterial green = ColorMaterial(Vec3(0.0, 0.8, 0.0));
    ColorMaterial blue  = ColorMaterial(Vec3(0.0, 0.0, 0.8));
    ColorMaterial white = ColorMaterial(Vec3(0.8, 0.8, 0.8));

    EmissiveMaterial light  = EmissiveMaterial(Vec3(1.0, 1.0, 1.0));
    EmissiveMaterial light2 = EmissiveMaterial(Vec3(0.5, 0.5, 0.5));

    StingrayScene *scene = new StingrayScene({
        new Sphere(Vec3(-0.5, 0, 1), 0.5,           &light),
        new Sphere(Vec3( 0.5, 0, 1), 0.5,           &blue),
        new Sphere(Vec3(-1.5, 0, 1), 0.5,           &green),
        new Sphere(Vec3( 1.5, 0, 1), 0.5,           &red),

        new Sphere(Vec3(0.0, -9999.5,  0.0), 9999.0, &white),
        new Sphere(Vec3(0.0, 10000,    0.0), 9999.0, &white),
        new Sphere(Vec3(-10001, 0.0,   0.0), 9999.0, &white),
        new Sphere(Vec3(10001 ,  0.0,  0.0), 9999.0, &white),
        new Sphere(Vec3(0.0, 0.0,  10000.5), 9999.0, &light2),
        new Sphere(Vec3(0.0, 0.0, -10000.5), 9999.0, &white)
    });

        // TODO: multithreading

    std::thread threads[MAX_THREADS];
    RenderBuffer *thread_imgs[MAX_THREADS];
    int thread_height = IMG_HEIGHT / MAX_THREADS;
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_imgs[i] = new RenderBuffer(IMG_WIDTH, thread_height);
        StingrayRenderer renderer = StingrayRenderer(*thread_imgs[i]);
        threads[i] = std::thread(std::bind(render, 0, 0, IMG_WIDTH - 1, thread_height - 1, 4, scene, i * thread_height, &renderer, i, IMG_HEIGHT));
        printf("Starting thread %d\n", i);
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        threads[i].join();
        memcpy(img.get_buffer() + i * thread_height * IMG_WIDTH * 3, thread_imgs[i]->get_buffer(), thread_height * IMG_WIDTH * 3);
        img.save("_sray_prog.png");
        printf("Thread %d exited\n", i);
    }
    printf("Rendering finished, denoising...\n");
    denoiser.denoise();

    img.save(filename);

    return 0;
}