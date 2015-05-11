#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "cmd.h"
#include "enum.h"
#include "pixel.h"

gpu_frame *gpu_frame_new(uint32_t width, uint32_t height) {
    gpu_frame *f = malloc(sizeof(gpu_frame));
    f->buf = malloc(width * height * 4);
    f->width = width;
    f->height = height;
    return f;
}

void gpu_frame_free(gpu_frame *frame) {
    free(frame->buf);
    free(frame);
}

void gpu_frame_clear(gpu_frame *frame, color_t color) {
    for (int y = 0; y < frame->height; y++) {
        for (int x = 0; x < frame->width; x++) {
            color_t *pixel = &frame->buf[y * frame->width + x];
            *pixel = color;
        }
    }
}

void gpu_frame_queue(gpu_frame *frame, gpu_cmd *cmd) {
    tack_push(&frame->queue, cmd);
    gpu_cmd_free(cmd);
}

void gpu_frame_render(gpu_frame *frame) {
    int len = tack_len(&frame->queue);
    for (int i = 0; i < len; i++) {
        gpu_cmd *cmd = tack_get(&frame->queue, i);
        gpu_cmd_draw(cmd, frame);
        gpu_cmd_free(cmd);
    }
}

void gpu_frame_blit(gpu_frame *frame, void *out, uint32_t type, uint32_t format) {
    memcpy(out, frame->buf, frame->width * frame->height * sizeof(color_t));
    return;
    pixel_convert(frame->buf, &out, frame->width, frame->height, GPU_RGBA, GPU_UNSIGNED_BYTE, type, format);
}
