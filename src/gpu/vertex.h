#ifndef GPU_VERTEX_H
#define GPU_VERTEX_H

#include <stddef.h>
#include <stdint.h>

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
    size_t len;
    pos_t *pos;
    color_t *color;
    tex_coord_t *tex;
} vertex_t;

#endif
