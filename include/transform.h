
#include "mat.h"

/* ----- Common ------- */

/* Converts degrees to radians */
float glv_radians(float deg);
/* Converts radians to degrees */
float glv_degrees(float rad);

/* ----- Matrix Creation ------ */

/* Returns a 4x4 orthographic projection matrix */
glv_mat4 glv_ortho2D(float left, float right, float bottom, float top);
glv_mat4 glv_ortho(float left, float right, float bottom, float top, float near, float far);

/* Generates a perspective 4x4 matrix */
glv_mat4 glv_frustum(float left, float right, float bottom, float top, float near, float far);
glv_mat4 glv_perspective(float fovy, float aspect, float near, float far);
glv_mat4 glv_perspective_fov(float fov, float width, float height, float near, float far);

/* Creates a look-at matrix (translation + rotation) */
glv_mat4 glv_lookat(const glv_vec3* eye, const glv_vec3* centre, const glv_vec3* up);


/* ----- Matrix Transform ----- */

/* Creates a 4x4 scaling matrix */
glv_mat4 glv_scale(const glv_mat4* mat, const glv_vec3* scales);

/* Creates a 4x4 translation matrix */
glv_mat4 glv_translate(const glv_mat4* mat, const glv_vec3* displacement);

/* Creates 4x4 rotation matrix with given angle in degrees and axis */
glv_mat4 glv_rotate(const glv_mat4* mat, float angle, const glv_vec3* axis);

/* Transforms a given vector by a transformation matrix */
glv_vec4 glv_transform(glv_vec4* v, glv_mat4* m);