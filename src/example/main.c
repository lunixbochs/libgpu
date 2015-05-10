#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

#include "gpu/cmd.h"
#include "gpu/enum.h"
#include "gpu/frame.h"
#include "gpu/mm.h"
#include "gpu/raster.h"
#include "gpu/vertex.h"
#include "util/matrix.h"

void draw_frame(uint8_t *frame_out, int counter) {
    mat4 *viewport = mat4_new();
    mat4_translate(viewport, (640 - 0.5f) / 2.0f, (480 - 0.5f) / 2.0f, -1.0f);
    mat4_scale(viewport, (640 - 0.5f) / 2.0f, -(480 - 0.5f) / 2.0f, 1.0f);

    float rotate = counter / 10;
    mat4 *model = mat4_new();
    mat4_translate(model, 0, 0, 10.0f);
    mat4_rotate(model, rotate, 1.0f, 1.0f, 0);
    mat4_translate(model, 3.0f, 0, 0);

    mat4 *model2 = mat4_clone(model);
    mat4_translate(model2, -6.0f, 0.0f, 0.0f);

    mat4 *view = mat4_new();
    mat4_perspective(view, 45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

    /*
    mat4_mul(model, view);
    mat4_mul(model, viewport);
    mat4_mul(model2, view);
    mat4_mul(model2, viewport);
    */

    gpu_frame *frame = gpu_frame_new(640, 480);
    color_t clear_color = {0x00, 0x00, 0x00, 0xFF};
    gpu_frame_clear(frame, clear_color);

    #include "shapes.h"

    vertex_t *v1 = vertex_new();
    v1->len = 36;
    v1->pos = memdup(cube3d, 36 * sizeof(pos_t));
    vertex_t *v2 = vertex_copy(v1);
    /*
    vertex_transform(model, v1, v1);
    vertex_transform(model2, v2, v2);
    */
    vertex_transform(model, v1, v1);
    vertex_transform(view, v1, v1);
    vertex_transform(viewport, v1, v1);
    vertex_transform(model2, v2, v2);
    vertex_transform(view, v2, v2);
    vertex_transform(viewport, v2, v2);

    gpu_cmd *cmd1 = gpu_cmd_new(GPU_TRIANGLE, v1, false);
    gpu_cmd *cmd2 = gpu_cmd_new(GPU_TRIANGLE, v2, true);
    gpu_cmd_draw(cmd1, frame);
    gpu_cmd_draw(cmd2, frame);
    gpu_frame_blit(frame, frame_out, GPU_RGBA, GPU_UNSIGNED_BYTE);
    gpu_frame_free(frame);
    free(cmd1);
    free(cmd2);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    SDL_Surface *screen = SDL_CreateRGBSurface(0, 640, 480, 32,
                                               0x00FF0000,
                                               0x0000FF00,
                                               0x000000FF,
                                               0xFF000000);
    SDL_Texture *sdlTexture = SDL_CreateTexture(renderer,
                                                SDL_PIXELFORMAT_ARGB8888,
                                                SDL_TEXTUREACCESS_STREAMING,
                                                640, 480);
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
        SDL_LockSurface(screen);
        draw_frame(screen->pixels, i);
        SDL_UnlockSurface(screen);
        SDL_UpdateTexture(sdlTexture, NULL, screen->pixels, screen->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
