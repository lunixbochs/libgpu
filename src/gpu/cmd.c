#include <stdlib.h>

#include "cmd.h"
#include "enum.h"
#include "raster.h"
#include "verts.h"

gpu_cmd *gpu_cmd_new(uint32_t primitive, gpu_verts *verts, bool wireframe) {
    gpu_cmd *cmd = malloc(sizeof(gpu_cmd));
    cmd->primitive = primitive;
    cmd->verts = verts;
    cmd->wireframe = wireframe;
    return cmd;
}

void gpu_cmd_free(gpu_cmd *cmd) {
    free(cmd->verts);
    free(cmd);
}

void gpu_cmd_draw(gpu_cmd *cmd, gpu_frame *frame) {
    switch (cmd->primitive) {
    case GPU_TRIANGLE:
        for (int i = 0; i < cmd->verts->len - 2; i += 3) {
            gpu_triangle(frame, cmd->verts, i, cmd->wireframe);
        }
        break;
    default:
        abort();
    }
}
