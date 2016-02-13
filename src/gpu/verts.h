#ifndef GPU_VERTS_H
#define GPU_VERTS_H

#include <stdint.h>
#include "types.h"
#include "matrix.h"

gpu_verts *gpu_verts_new(uint32_t size);
gpu_verts *gpu_verts_copy(gpu_verts *in);
void gpu_verts_free(gpu_verts *v);
gpu_verts *gpu_verts_transform(mat4 *mat, gpu_verts *out, gpu_verts *in);

#endif
