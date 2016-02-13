#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "cmd.h"
#include "enum.h"
#include "pixel.h"

gpu_frame gpu_frame_init(void *buf, uint32_t width, uint32_t height) {
    return (gpu_frame){
        .buf = buf,
        .width = width,
        .height = height,
    };
}

void gpu_frame_clear(gpu_frame *frame, gpu_color color) {
    for (int y = 0; y < frame->height; y++) {
        for (int x = 0; x < frame->width; x++) {
            gpu_color *pixel = &frame->buf[y * frame->width + x];
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
