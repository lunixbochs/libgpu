#include <stdlib.h>

#include "cmd.h"
#include "enum.h"
#include "raster.h"

gpu_cmd *gpu_cmd_new(uint32_t primitive, vertex_t *verts) {
    gpu_cmd *cmd = malloc(sizeof(gpu_cmd));
    cmd->primitive = primitive;
    cmd->verts = verts;
    return cmd;
}

void gpu_cmd_draw(gpu_cmd *cmd, gpu_frame *frame) {
    /*
    switch (cmd->primitive) {
    case GPU_TRIANGLE:
    default:
        abort();
    }
    */
    for (int i = 0; i < cmd->verts->len; i++) {
        gpu_triangle(frame->buf, (float *)&cmd->verts->pos[i], 0);
    }
}

void gpu_cmd_decref(gpu_cmd *cmd) {

}

void gpu_cmd_incref(gpu_cmd *cmd) {

}
