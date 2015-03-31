#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#ifndef MIN
#define MIN(a, b) (((a) < (b) ? (a) : (b)))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b) ? (a) : (b)))
#endif

void gpu_pixel(uint8_t *frame, int x, int y) {
    uint8_t *pixel = &frame[x * 4 + y * 640 * 4];
    pixel[0] = 0xFF;
    pixel[1] = 0xFF;
    pixel[2] = 0xFF;
    pixel[3] = 0xFF;
}

void gpu_line(uint8_t *frame, float a[3], float b[3]) {
    float x1, y1, x2, y2;
    x1 = a[0], y1 = a[1];
    x2 = b[0], y2 = b[1];
    float slope = (y2 - y1) / (x2 - x1);
    if (x1 == x2) {
        for (float y = MIN(y1, y2); y < MAX(y1, y2); y++) {
            gpu_pixel(frame, x1, y);
        }
    } else {
        for (float x = MIN(x1, x2); x < MAX(x1, x2); x++) {
            float y = slope * (x - MIN(x1, x2)) + y1;
            gpu_pixel(frame, x, y);
        }
    }
}

void gpu_triangle(uint8_t *frame, float a, float b, float c, float d, float e, float f) {
    mat4 *viewport = mat4_new();
    mat4_translate(viewport, (640 - 0.5f) / 2.0f, (480 - 0.5f) / 2.0f, 0.0f);
    mat4_scale(viewport, (640 - 0.5f) / 2.0f, -(480 - 0.5f) / 2.0f, 1.0f);

    float verts[] = {
        a, b, 1.0f,
        c, d, 1.0f,
        e, f, 1.0f,
    };

    for (int i = 0; i < 3; i++) {
        float *v = &verts[i * 3];
        mat4_mul_vec3(viewport, v, v);
    }
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        gpu_line(frame, &verts[i * 3], &verts[next * 3]);
    }
}

void gpu_frame(uint8_t *frame, int i) {
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            uint8_t *pixel = &frame[y * 640 * 4 + x * 4];
            pixel[0] = 0x00;
            pixel[1] = 0x00;
            pixel[2] = 0x00;
            pixel[3] = 0xFF;
        }
    }
    gpu_triangle(frame, -1, -1, 0, 1, 1, -1);
}
