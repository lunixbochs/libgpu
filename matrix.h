#include "vectorial/simd4f.h"
#include "vectorial/simd4x4f.h"

typedef simd4x4f mat4;

mat4 *mat4_transpose(mat4 *m) {
    simd4x4f_transpose_inplace(m);
    return m;
}

mat4 *mat4_identity(mat4 *m) {
    simd4x4f_identity(m);
    return m;
}

mat4 *mat4_new() {
    mat4 *m = malloc(sizeof(mat4));
    return mat4_identity(m);
}

mat4 *mat4_load(mat4 *m, float *load) {
    simd4x4f_uload(m, load);
    return m;
}

void mat4_save(mat4 *m, float *out) {
    simd4x4f_ustore(m, out);
}

mat4 *mat4_mul(mat4 *m, mat4 *quotient) {
    simd4x4f out;
    simd4x4f_matrix_mul(m, quotient, &out);
    *m = out;
    return m;
}

mat4 *mat4_rotate(mat4 *m, float angle, float x, float y, float z) {
    float radians = angle * VECTORIAL_PI / 180;
    simd4x4f rotate, out;
    simd4x4f_axis_rotation(&rotate, radians, simd4f_create(x, y, z, 1.0f));
    simd4x4f_matrix_mul(m, &rotate, &out);
    *m = out;
    return m;
}

mat4 *mat4_scale(mat4 *m, float x, float y, float z) {
    simd4x4f scale, out;
    simd4x4f_scaling(&scale, x, y, z);
    simd4x4f_matrix_mul(m, &scale, &out);
    *m = out;
    return m;
}

mat4 *mat4_translate(mat4 *m, float x, float y, float z) {
    simd4x4f translate, out;
    simd4x4f_translation(&translate, x, y, z);
    simd4x4f_matrix_mul(m, &translate, &out);
    *m = out;
    return m;
}

mat4 *mat4_ortho(mat4 *m, float left, float right,
                          float bottom, float top,
                          float near, float far) {
    simd4x4f ortho, out;
    simd4x4f_ortho(&ortho, left, right, bottom, top, near, far);
    simd4x4f_matrix_mul(m, &ortho, &out);
    *m = out;
    return m;
}

mat4 *mat4_frustum(mat4 *m, float left, float right,
                            float bottom, float top,
                            float near, float far) {
    simd4x4f frustum, out;
    simd4x4f_frustum(&frustum, left, right, bottom, top, near, far);
    simd4x4f_matrix_mul(m, &frustum, &out);
    *m = out;
    return m;
}

mat4 *mat4_perspective(mat4 *m, float fov, float aspect, float znear, float zfar) {
    simd4x4f perspective, out;
    simd4x4f_perspective(&perspective, fov, aspect, znear, zfar);
    simd4x4f_matrix_mul(m, &perspective, &out);
    *m = out;
    return m;
}

void mat4_mul_vec2(mat4 *m, float out[2], const float in[2]) {
    simd4f tmp, vert = simd4f_create(in[0], in[1], 0.0f, 1.0f);
    simd4x4f_matrix_vector_mul(m, &vert, &tmp);
    tmp = simd4f_div(tmp, simd4f_splat_w(tmp));
    simd4f_ustore3(tmp, out);
}

void mat4_mul_vec3(mat4 *m, float out[3], const float in[3]) {
    simd4f tmp, vert = simd4f_create(in[0], in[1], in[2], 1.0f);
    simd4x4f_matrix_vector_mul(m, &vert, &tmp);
    tmp = simd4f_div(tmp, simd4f_splat_w(tmp));
    simd4f_ustore3(tmp, out);
}

void mat4_mul_vec4(mat4 *m, float out[4], const float in[4]) {
    simd4f coord = simd4f_create(in[0], in[1], in[2], in[3]);
    simd4f tmp;
    simd4x4f_matrix_vector_mul(m, &coord, &tmp);
    simd4f_ustore4(coord, out);
}
