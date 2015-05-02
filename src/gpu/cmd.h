#ifndef GPU_CMD_H
#define GPU_CMD_H

#include "types.h"

extern void gpu_cmd_incref(gpu_cmd *);
extern void gpu_cmd_decref(gpu_cmd *);
extern void gpu_cmd_draw(gpu_frame *, gpu_cmd *);

#endif
