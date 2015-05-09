#ifndef GPU_GPU_H
#define GPU_GPU_H

#include <stdint.h>

extern void gpu_clear(uint8_t *frame, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
extern void gpu_triangle(uint8_t *frame, float *verts, float rotate, float offset, bool fill);

#endif
