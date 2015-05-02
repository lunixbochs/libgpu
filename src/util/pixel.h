#ifndef PIXEL_H
#define PIXEL_H

#include <GL/gl.h>
#include <stdbool.h>

typedef struct {
    uint32_t type;
    int32_t red, green, blue, alpha;
} colorlayout_t;

typedef struct {
    float r, g, b, a;
} pixel_t;

bool pixel_convert(const void *src, void **dst,
                   uint32_t width, uint32_t height,
                   uint32_t src_format, uint32_t src_type,
                   uint32_t dst_format, uint32_t dst_type);

bool pixel_convert_direct(const void *src, void *dst, uint32_t pixels,
                          uint32_t src_format, uint32_t src_type, size_t src_stride,
                          uint32_t dst_format, uint32_t dst_type, size_t dst_stride);

bool pixel_scale(const void *src, void **dst,
                  uint32_t width, uint32_t height,
                  float ratio,
                  uint32_t format, uint32_t type);

bool pixel_to_ppm(const void *pixels,
                  uint32_t width, uint32_t height,
                  uint32_t format, uint32_t type, uint32_t name);

#endif
