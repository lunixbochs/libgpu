#include <stdlib.h>

#include "matrix.h"
#include "vertex.h"

vertex_t *vertex_new() {
    return calloc(1, sizeof(vertex_t));
}

vertex_t *vertex_copy(vertex_t *in) {
    vertex_t *out = malloc(sizeof(vertex_t));
    out->pos = in->pos;
    out->color = in->color;
    out->tex = in->tex;
    return out;
}

vertex_t *vertex_transform(mat4 *mat, vertex_t *out, vertex_t *in) {
    if (out == NULL) {
        out = vertex_copy(in);
    }
    for (int i = 0; i < in->len; i++) {
        mat4_mul_vec3(mat, (float *)&out->pos[i], (float *)&in->pos[i]);
    }
    return out;
}
