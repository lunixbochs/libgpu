#ifndef GPU_CMD_H
#define GPU_CMD_H

#include "types.h"

extern gpu_cmd *gpu_cmd_new(uint32_t primitive, gpu_verts *verts, bool wireframe);
extern void gpu_cmd_free(gpu_cmd *cmd);
extern void gpu_cmd_draw(gpu_cmd *cmd, gpu_frame *frame);

#endif
