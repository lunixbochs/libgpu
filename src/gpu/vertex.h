#include <stdint.h>

typedef struct {
    uint8_t r, g, b, a;
    float x, y, z;
    float s, t, r, q;
} vertex_t;

vertex_t *vertex_transform(mat, out, in) {
    if (out == NULL) {
        out = malloc(sizeof(in));
    }
    for (int i = 0; i < count; i++) {
        transform(out[i], in[i])
    }
}
