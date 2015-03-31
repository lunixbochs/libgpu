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

#ifndef ABS
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif

void gpu_pixel(uint8_t *frame, int x, int y) {
    if (x < 0 || x >= 640 || y < 0 || y >= 480) return;
    uint8_t *pixel = &frame[x * 4 + y * 640 * 4];
    pixel[0] = 0xFF;
    pixel[1] = 0xFF;
    pixel[2] = 0xFF;
    pixel[3] = 0xFF;
}

void gpu_line(uint8_t *frame, float a[2], float b[2]) {
    float x1, y1, x2, y2;
    x1 = a[0], y1 = a[1];
    x2 = b[0], y2 = b[1];
    if ((x1 < 0 || x1 >= 640) && (x2 < 0 || x2 >= 640)) {
        return;
    }
    if ((y1 < 0 || y1 >= 480) && (y2 < 0 || y2 >= 480)) {
        return;
    }
    float slope = (y2 - y1) / (x2 - x1);
    float xd;
    if (slope > 1 || slope < -1) {
        xd = 1 / MIN(ABS(slope), 480);
    } else {
        xd = 1;
    }
    if (x1 == x2) {
        for (float y = MAX(MIN(y1, y2), 0); y < MIN(MAX(y1, y2), 480); y++) {
            gpu_pixel(frame, x1, y);
        }
    } else if (x1 < x2) {
        for (float x = MAX(x1, 0); x < MIN(x2, 640); x += xd) {
            float y = slope * (x - x1) + y1;
            gpu_pixel(frame, x, y);
        }
    } else {
        for (float x = MAX(x2, 0); x < MIN(x1, 640); x += xd) {
            float y = slope * (x - x2) + y2;
            gpu_pixel(frame, x, y);
        }
    }
}

void gpu_triangle(uint8_t *frame, float *verts, float rotate) {
    mat4 *viewport = mat4_new();
    mat4_translate(viewport, (640 - 0.5f) / 2.0f, (480 - 0.5f) / 2.0f, -1.0f);
    mat4_scale(viewport, (640 - 0.5f) / 2.0f, -(480 - 0.5f) / 2.0f, 1.0f);

    mat4 *model = mat4_new();
    mat4_translate(model, 3.0f, 0, 10.0f);
    mat4_rotate(model, rotate, 1.0f, 0, 0);

    mat4 *view = mat4_new();
    mat4_perspective(view, 45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

    for (int i = 0; i < 3; i++) {
        float *v = &verts[i * 3];
        mat4_mul_vec3(model, v, v);
        mat4_mul_vec3(view, v, v);
        mat4_mul_vec3(viewport, v, v);
    }
    for (int i = 0; i < 3; i++) {
        int next = (i + 1) % 3;
        gpu_line(frame, &verts[i * 3], &verts[next * 3]);
    }
}

void gpu_frame(uint8_t *frame, int counter) {
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            uint8_t *pixel = &frame[y * 640 * 4 + x * 4];
            pixel[0] = 0x00;
            pixel[1] = 0x00;
            pixel[2] = 0x00;
            pixel[3] = 0xFF;
        }
    }
    float tri3d[] = {
        // front
        0, 1, 0,
        -1, -1, 1,
        1, -1, 1,

        // right
        0, 1, 0,
        1, -1, 1,
        1, -1, -1,

        // back
        0, 1, 0,
        1, -1, -1,
        -1, -1, -1,

        // left
        0, 1, 0,
        -1, -1, -1,
        -1, -1, 1,
    };

    float cube3d[] = {
        1, 1, -1,
        -1, 1, -1,
        1, 1, 1,

        -1, 1, -1,
        -1, 1, 1,
        1, 1, 1,

        1, -1 ,1,
        -1 ,-1, 1,
        1, -1, -1,

        -1, -1, 1,
        -1, -1, -1,
        1, -1, -1,

        1, 1, 1,
        -1, 1, 1,
        1, -1, 1,

        -1, 1, 1,
        -1, -1, 1,
        1, -1, 1,

        1, -1, -1,
        -1, -1, -1,
        1, 1, -1,

        -1, -1, -1,
        -1, 1, -1,
        1, 1, -1,

        -1, 1, 1,
        -1, 1, -1,
        -1, -1, 1,

        -1, 1, -1,
        -1, -1, -1,
        -1, -1, 1,

        1, 1, -1,
        1, 1, 1,
        1, -1, -1,

        1, 1, 1,
        1, -1, 1,
        1, -1, -1,
    };
    for (int i = 0; i < 4; i++) {
//        gpu_triangle(frame, &tri3d[i * 9], counter / 2);
    }
    for (int i = 0; i < 12; i++) {
        gpu_triangle(frame, &cube3d[i * 9], counter / 2);
    }
}
