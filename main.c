#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

extern void *gpu_frame(uint8_t *frame, int i);

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("libgpu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Surface *tmp = SDL_CreateRGBSurface(0, 640, 480, 32, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);
    int i = 0;
    bool done = false;
    SDL_Event event;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
            }
        }
        SDL_LockSurface(tmp);
        gpu_frame(tmp->pixels, i++);
        SDL_UnlockSurface(tmp);
        SDL_BlitSurface(tmp, NULL, screen, NULL);
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
