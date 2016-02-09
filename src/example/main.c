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

void draw_frame(uint8_t *frame_out, int width, int height, int counter) {
    mat4 viewport = mat4_new();
    mat4_translate(&viewport, (width - 0.5f) / 2.0f, (height - 0.5f) / 2.0f, -1.0f);
    mat4_scale(&viewport, (width - 0.5f) / 2.0f, -(height - 0.5f) / 2.0f, 1.0f);

    float rotate = counter / 10.0;
    mat4 model = mat4_new();
    mat4_translate(&model, 0, 0, 10.0f);
    mat4_rotate(&model, rotate, 1.0f, 1.0f, 0);
    mat4_translate(&model, 3.0f, 0, 0);

    mat4 model2 = model;
    mat4_translate(&model2, -6.0f, 0.0f, 0.0f);

    mat4 view = mat4_new();
    mat4_perspective(&view, 45.0f, (float)width / (float)height, 0.1f, 100.0f);

    /*
    mat4_mul(model, view);
    mat4_mul(model, viewport);
    mat4_mul(model2, view);
    mat4_mul(model2, viewport);
    */

    gpu_frame frame = gpu_frame_init(frame_out, width, height);
    color_t clear_color = {0x00, 0x00, 0x00, 0xFF};
    gpu_frame_clear(&frame, clear_color);

    #include "shapes.h"

    vertex_t *v1 = vertex_new();
    v1->len = 36;
    v1->pos = memdup(cube3d, 36 * sizeof(pos_t));
    vertex_t *v2 = vertex_copy(v1);
    /*
    vertex_transform(model, v1, v1);
    vertex_transform(model2, v2, v2);
    */
    vertex_transform(&model, v1, v1);
    vertex_transform(&view, v1, v1);
    vertex_transform(&viewport, v1, v1);
    vertex_transform(&model2, v2, v2);
    vertex_transform(&view, v2, v2);
    vertex_transform(&viewport, v2, v2);

    gpu_cmd *cmd1 = gpu_cmd_new(GPU_TRIANGLE, v1, false);
    gpu_cmd *cmd2 = gpu_cmd_new(GPU_TRIANGLE, v2, true);
    gpu_cmd_draw(cmd1, &frame);
    gpu_cmd_draw(cmd2, &frame);
    free(cmd1);
    free(cmd2);
}

int main() {
    int width = 1280;
    int height = 720;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_Texture *texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            width, height);
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
                case SDL_WINDOWEVENT_RESIZED:
                    width = event.window.data1;
                    height = event.window.data2;
                    SDL_DestroyTexture(texture);
                    SDL_Texture *texture = SDL_CreateTexture(renderer,
                            SDL_PIXELFORMAT_ARGB8888,
                            SDL_TEXTUREACCESS_STREAMING,
                            width, height);
                    break;
            }
        }
        void *pixels = NULL;
        int pitch = 0;
        SDL_LockTexture(texture, NULL, &pixels, &pitch);
        draw_frame(pixels, width, height, i);
        if (!click) {
            i += 10;
        }
        SDL_UnlockTexture(texture);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
