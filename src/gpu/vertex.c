#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "mm.h"
#include "vertex.h"

vertex_t *vertex_new() {
    return calloc(1, sizeof(vertex_t));
}

void vertex_free(vertex_t *v) {
    free(v->pos);
    free(v->color);
    free(v->tex);
    free(v);
}

vertex_t *vertex_copy(vertex_t *in) {
    vertex_t *out = malloc(sizeof(vertex_t));
    out->len = in->len;
    out->pos = memdup(in->pos, in->len * sizeof(pos_t));
    out->color = memdup(in->pos, in->len * sizeof(color_t));
    out->tex = memdup(in->pos, in->len * sizeof(tex_t));
    return out;
}

vertex_t *vertex_transform(mat4 *mat, vertex_t *out, vertex_t *in) {
    if (out == NULL) {
        out = vertex_copy(in);
    }
    for (int i = 0; i < in->len; i++) {
        pos_t *po = &out->pos[i], *pi = &in->pos[i];
        mat4_mul_vec3(mat, (float *)po, (float *)pi);
    }
    return out;
}
