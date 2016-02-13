#ifndef GPU_TYPES_H
#define GPU_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tack.h"

typedef struct {
    float x, y, z;
} gpu_pos;

typedef struct {
    uint8_t r, g, b, a;
} gpu_color;

typedef struct {
    float s, t, r, q;
} gpu_tex_coord;

typedef struct {
    gpu_pos pos;
    gpu_color color;
    gpu_tex_coord tex;
} gpu_vert;

typedef struct {
    uint32_t len;
    gpu_vert *v;
} gpu_verts;

typedef struct {
    uint32_t width, height;
    gpu_color data[];
} gpu_tex;

typedef struct {
    uint32_t width, height;
    tack_t queue;
    gpu_color *buf;
} gpu_frame;

typedef struct {
    uint32_t primitive;
    gpu_verts *verts;
    bool wireframe;
} gpu_cmd;

#endif
