#ifndef GPU_TYPES_H
#define GPU_TYPES_H

#include <stdint.h>
#include "tack.h"

typedef struct {
    void *buf;
    uint32_t width, height;
    tack_t queue;
} gpu_frame;

typedef struct {

} gpu_cmd;

#endif
