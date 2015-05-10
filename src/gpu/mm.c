#include <stdlib.h>
#include <string.h>

#include "mm.h"

void *memdup(void *src, size_t size) {
    void *dst = malloc(size);
    memcpy(dst, src, size);
    return dst;
}
