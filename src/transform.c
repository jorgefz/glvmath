
#include <math.h>
#include "transform.h"

/* ----- Common ------- */

/* Converts degrees to radians */
float glv_radians(float deg){
    return deg * M_PI / 180.0f;
}

/* Converts radians to degrees */
float glv_degrees(float rad){
    return rad * 180.0f / M_PI;
}


/* ----- Matrix Creation ----- */

/* Returns a 4x4 orthographic projection matrix */
glv_mat4 glv_ortho2D(float left, float right, float bottom, float top){
    glv_mat4 m = {0};
    m.data[0][0] = 2.0f/(right-left);
    m.data[1][1] = 2.0f/(top-bottom);
    m.data[2][2] = -1.0f;
    m.data[3][3] = 1.0f;

    m.data[0][3] = - (right + left) / (right - left);
    m.data[1][3] = - (top + bottom) / (top - bottom);
    return m;
}

glv_mat4 glv_ortho(float left, float right, float bottom, float top, float near, float far){
    // uses right-handed [-1,1] clip space.
    glv_mat4 m = {0};
    m.data[0][0] = 2.0f/(right-left);
    m.data[1][1] = 2.0f/(top-bottom);
    m.data[2][2] = -2.0f/(far-near);
    m.data[3][3] = 1.0f;

    m.data[0][3] = - (right + left) / (right - left);
    m.data[1][3] = - (top + bottom) / (top - bottom);
    m.data[2][3] = - (far + near) / (far - near);
    return m;
}

glv_mat4 glv_frustum(float left, float right, float bottom, float top, float near, float far){
    // uses right-handed [-1,1] clip space.
    glv_mat4 m = {0};

    m.data[0][0] = 2.0 * near / (right - left);
    m.data[1][1] = 2.0 * near / (top - bottom);
    m.data[2][2] = - (far + near) / (far - near);

    m.data[0][2] = (right + left) / (right - left);
    m.data[2][2] = - (far + near) / (far - near);
    m.data[3][2] = -1.0f;
    m.data[2][3] = - 2.0f * far * near / (far - near);

    return m;
}

glv_mat4 glv_perspective(float fovy, float aspect, float near, float far){
    // uses right-handed [-1,1] clip space.
    #ifdef GLV_USE_DEGREES
        a = glv_radians(fovy);
    #endif
    float h = near * tanf(fovy / 2.0f);
    float w = aspect * h;
    return glv_frustum(-w, w, -h, h, near, far);
}

glv_mat4 glv_perspective_fov(float fov, float width, float height, float near, float far){
    return glv_perspective(fov, height / width, near, far);
}

/* View transformation matrix (world to view coords) */
glv_mat4 glv_lookat(const glv_vec3* eye, const glv_vec3* centre, const glv_vec3* up) {
    // uses right-handed clip space.
    glv_vec3 f, s, u;
    f = glv_vec3_normalize(&(glv_vec3){
        .x = centre->x - eye->x,
        .y = centre->y - eye->y,
        .z = centre->z - eye->z
    });
    s = glv_vec3_cross(&f, up);
    s = glv_vec3_normalize(&s);
    u = glv_vec3_cross(&s, &f);

    glv_mat4 m = glv_mat4_identity();
    m.data[0][0] = s.x;
    m.data[0][1] = s.y;
    m.data[0][2] = s.z;

    m.data[1][0] = u.x;
    m.data[1][1] = u.y;
    m.data[1][2] = u.z;

    m.data[2][0] = -f.x;
    m.data[2][1] = -f.y;
    m.data[2][2] = -f.z;

    m.data[3][0] = -glv_vec3_dot(&s, eye);
    m.data[3][1] = -glv_vec3_dot(&u, eye);
    m.data[3][2] = -glv_vec3_dot(&f, eye);

    return m;
}

/* ----- Matrix Transform ----- */
glv_mat4 glv_scale(const glv_mat4* m, const glv_vec3* v){
    // Matrix scaling works by scaling the diagonal elements.
    glv_mat4 s = glv_mat4_diagonal(v->x, v->y, v->z, 1.0f);
    return glv_mat4_multiply(m, &s);
}

glv_mat4 glv_translate(const glv_mat4* m, const glv_vec3* v){
    // Matrix translation works by scaling the fourth matrix column. 
    glv_mat4 t = glv_mat4_identity();
    t.data[0][3] = v->x;
    t.data[1][3] = v->y;
    t.data[2][3] = v->z;
    return glv_mat4_multiply(m, &t);
}

/* Creates a rotation transformation matrix */
glv_mat4 glv_rotate(const glv_mat4* m, float a, const glv_vec3* v){

    #ifdef GLV_USE_DEGREES
        a = glv_radians(a);
    #endif

    const float c = cosf(a); // radians
    const float s = sinf(a); // radians
    glv_vec3 axis = glv_vec3_normalize(v);

    glv_vec3 temp = {
        .x = (1.0 - c) * axis.x,
        .y = (1.0 - c) * axis.y,
        .z = (1.0 - c) * axis.z
    };

    glv_mat4 rot = {0};
    rot.data[0][0] = c + temp.x * axis.x;
    rot.data[1][0] = temp.x * axis.y + s * axis.z;
    rot.data[2][0] = temp.x * axis.z - s * axis.y;

    rot.data[0][1] = temp.y * axis.x - s * axis.z;
    rot.data[1][1] = c + temp.y * axis.y;
    rot.data[2][1] = temp.y * axis.z + s * axis.x;

    rot.data[0][2] = temp.z * axis.x + s * axis.y;
    rot.data[1][2] = temp.z * axis.y - s * axis.x;
    rot.data[2][2] = c + temp.z * axis.z;

    glv_mat4 res = {0};
    unsigned int i;
    for(i=0; i!=GLV_MAT4_RANK; ++i) {
        res.data[i][0] = m->data[i][0] * rot.data[0][0] + m->data[i][1] * rot.data[1][0] + m->data[i][2] * rot.data[2][0];
        res.data[i][1] = m->data[i][0] * rot.data[0][1] + m->data[i][1] * rot.data[1][1] + m->data[i][2] * rot.data[2][1];
        res.data[i][2] = m->data[i][0] * rot.data[0][2] + m->data[i][1] * rot.data[1][2] + m->data[i][2] * rot.data[2][2];
        res.data[i][3] = m->data[i][3];
    }
    return res;
}


/* Transforms a given vector by a transformation matrix */
glv_vec4 glv_transform(glv_vec4* v, glv_mat4* m){
    glv_vec4 t = {0};
    unsigned int i, j;
    for(i = 0; i != GLV_MAT4_RANK; ++i){
        for(j = 0; j != GLV_MAT4_RANK; ++j){
            t.data[i] += v->data[j] * m->data[i][j];
        }
    }
    return t;
}