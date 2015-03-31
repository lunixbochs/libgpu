#include <SDL2/SDL.h>
#include <stdint.h>

extern void *gpu_frame();

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("libgpu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_Surface *tmp = SDL_CreateRGBSurface(0, 640, 480, 32, 0xFF, 0xFF00, 0xFF0000, 0xFF000000);
    SDL_LockSurface(tmp);
    void *frame = gpu_frame();
    memcpy(tmp->pixels, frame, tmp->h * tmp->w * 4);
    SDL_UnlockSurface(tmp);
    SDL_BlitSurface(tmp, NULL, screen, NULL);
    SDL_FreeSurface(tmp);

    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
