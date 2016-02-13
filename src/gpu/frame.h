#ifndef GPU_FRAME_H
#define GPU_FRAME_H

#include "types.h"

gpu_frame gpu_frame_init(void *buf, uint32_t width, uint32_t height);
void gpu_frame_clear(gpu_frame *frame, gpu_color color);
void gpu_frame_queue(gpu_frame *frame, gpu_cmd *cmd);
void gpu_frame_render(gpu_frame *frame);

#endif
