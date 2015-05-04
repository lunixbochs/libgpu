#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

#include "gpu/gpu.h"

void draw_frame(uint8_t *frame, int counter) {
    gpu_clear(frame, 0x00, 0x00, 0x00, 0xFF);
    #include "shapes.h"

    /*
    float tri2d1[9] = {
        0, 0, 0,
        1, 1, 0,
        1, -1, 0,
    };
    gpu_triangle(frame, tri2d1, counter, 0, 0);
    float tri2d2[9] = {
        0, 0, 0,
        1, 1, 0,
        1, -1, 0,
    };
    gpu_triangle(frame, tri2d2, counter, -3, 1);
    */

    for (int i = 0; i < 4; i++) {
//        gpu_triangle(frame, &tri3d[i * 9], counter / 2);
    }
    for (int i = 0; i < 12; i++) {
        gpu_triangle(frame, &cube3d[i * 9], counter / 10, 0, 1);
    }
    for (int i = 0; i < 12; i++) {
        gpu_triangle(frame, &cube3d[i * 9], counter / 10, -6, 0);
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("libgpu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Surface *tmp = SDL_CreateRGBSurface(0, 640, 480, 32, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);
    int i = 0;
    bool done = false;
    bool click = false;
    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    click = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    click = false;
                    break;
                case SDL_MOUSEMOTION:
                    if (click) {
                        i += (event.motion.xrel + event.motion.yrel) * 10;
                    }
                    break;
            }
        }
        SDL_LockSurface(tmp);
        draw_frame(tmp->pixels, i);
        SDL_UnlockSurface(tmp);
        SDL_BlitSurface(tmp, NULL, screen, NULL);
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
