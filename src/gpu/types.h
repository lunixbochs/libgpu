#ifndef GPU_TYPES_H
#define GPU_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tack.h"

typedef struct {
    float x, y, z;
} pos_t;

typedef struct {
    uint8_t r, g, b, a;
} color_t;

typedef struct {
    float s, t, r, q;
} tex_coord_t;

typedef struct {
    uint32_t len;
    pos_t *pos;
    color_t *color;
    tex_coord_t *tex;
} vertex_t;

typedef struct {
    uint32_t width, height;
    color_t data[];
} tex_t;

typedef struct {
    color_t *buf;
    uint32_t width, height;
    tack_t queue;
} gpu_frame;

typedef struct {
    uint32_t primitive;
    vertex_t *verts;
    bool wireframe;
} gpu_cmd;

#endif
