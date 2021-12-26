
#include <math.h>
#include "vec.h"

/* Returns the length of the vector */
float glv_vec2_magnitude(const glv_vec2* v){
    return sqrtf(v->x*v->x + v->y*v->y);
}
float glv_vec3_magnitude(const glv_vec3* v){
    return sqrtf(v->x*v->x + v->y*v->y + v->z*v->z);
}
float glv_vec4_magnitude(const glv_vec4* v){
    return sqrtf(v->x*v->x + v->y*v->y + v->z*v->z + v->w*v->w);
}

/* Scales vector to have length of 1 */
glv_vec2 glv_vec2_normalize(const glv_vec2* v){
    float m = glv_vec2_magnitude(v);
    glv_vec2 n = {.x=v->x/m, .y=v->y/m};
    return n;
}
glv_vec3 glv_vec3_normalize(const glv_vec3* v){
    float m = glv_vec3_magnitude(v);
    glv_vec3 n = {.x=v->x/m, .y=v->y/m, .z=v->z/m};
    return n;
}
glv_vec4 glv_vec4_normalize(const glv_vec4* v){
    float m = glv_vec4_magnitude(v);
    glv_vec4 n = {.x=v->x/m, .y=v->y/m, .z=v->z/m, .w=v->w/m};
    return n;
}

/* Calculates dot product */
float glv_vec2_dot(const glv_vec2* v1, const glv_vec2* v2){
    return (v1->x * v2->x + v1->y * v2->y);
}
float glv_vec3_dot(const glv_vec3* v1, const glv_vec3* v2){
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
float glv_vec4_dot(const glv_vec4* v1, const glv_vec4* v2){
    return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
}

/* Calculates cross product */
glv_vec3 glv_vec3_cross(const glv_vec3* v1, const glv_vec3* v2){
    float x, y, z;
    x = v1->y * v2->z - v1->z * v2->y;
    y = v1->x * v2->z - v1->z * v2->x;
    z = v1->x * v2->y - v1->y * v2->x;
    return (glv_vec3){.x = x, .y = y, .z = z};
}
