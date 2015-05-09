#ifndef GPU_CMD_H
#define GPU_CMD_H

#include "types.h"

extern gpu_cmd *gpu_cmd_new(uint32_t primitive, vertex_t *verts);
extern void gpu_cmd_incref(gpu_cmd *cmd);
extern void gpu_cmd_decref(gpu_cmd *cmd);
extern void gpu_cmd_draw(gpu_cmd *cmd, gpu_frame *frame);

#endif
