#ifndef GPU_VERTEX_H
#define GPU_VERTEX_H

#include "types.h"
#include "matrix.h"

vertex_t *vertex_new();
void vertex_free(vertex_t *v);
vertex_t *vertex_copy(vertex_t *in);
vertex_t *vertex_transform(mat4 *mat, vertex_t *out, vertex_t *in);

#endif
