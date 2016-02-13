#include <stdlib.h>

#include "mm.h"
#include "verts.h"

gpu_verts *gpu_verts_new(uint32_t len) {
    gpu_verts *v = malloc(sizeof(gpu_verts));
    v->len = len;
    v->v = malloc(sizeof(gpu_vert) * len);
    return v;
}

gpu_verts *gpu_verts_copy(gpu_verts *in) {
    gpu_verts *out = gpu_verts_new(in->len);
    memcpy(out->v, in->v, sizeof(gpu_vert) * in->len);
    return out;
}

void gpu_verts_free(gpu_verts *v) {
    free(v->v);
    free(v);
}

gpu_verts *gpu_verts_transform(mat4 *mat, gpu_verts *out, gpu_verts *in) {
    if (out == NULL) {
        out = gpu_verts_copy(in);
    }
    for (int i = 0; i < in->len; i++) {
        gpu_pos *po = &out->v[i].pos, *pi = &in->v[i].pos;
        mat4_mul_vec3(mat, (float *)po, (float *)pi);
    }
    return out;
}
