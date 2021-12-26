/*

    === mat.h ===

    Matrix definitions and transforms,
    following GLSL style.

*/


#ifndef GLV_MAT_H
#define GLV_MAT_H 1

#include "vec.h"

#define GLV_MAT2_RANK 2
#define GLV_MAT3_RANK 3
#define GLV_MAT4_RANK 4

/* Square matrix definitions */
typedef struct{ float data[2][2]; } glv_mat2;
typedef struct{ float data[3][3]; } glv_mat3;
typedef struct{ float data[4][4]; } glv_mat4;

/*
// Additional matrix definitions
typedef struct{ float data[2][3] } glv_mat2x3;
typedef struct{ float data[2][4] } glv_mat2x4;
typedef struct{ float data[3][2] } glv_mat3x2;
typedef struct{ float data[3][4] } glv_mat3x4;
typedef struct{ float data[4][2] } glv_mat4x2;
typedef struct{ float data[4][3] } glv_mat4x3;
*/


/*
    ===== FUNCTION DECLARATIONS =====
*/

/* ----- Matrix Creation ----- */

/* Returns a 4x4 diagonal matrix with given diagonal elements */
glv_mat4 glv_mat4_diagonal(float e00, float e11, float e22, float e33);

/* Returns an 4x4 identity matrix */
glv_mat4 glv_mat4_identity();

/* ----- Matrix Operations ----- */
/* Returns the transpose matrix */
glv_mat2 glv_mat2_transpose(const glv_mat2* mat);
glv_mat3 glv_mat3_transpose(const glv_mat3* mat);
glv_mat4 glv_mat4_transpose(const glv_mat4* mat);

/* Returns the minor of a matrix at i,j */
float glv_mat3_minor(const glv_mat3* m, unsigned int i, unsigned int j);
float glv_mat4_minor(const glv_mat4* m, unsigned int i, unsigned int j);

/* Returns the determinant of a matrix */
float glv_mat2_determinant(const glv_mat2* mat);
float glv_mat3_determinant(const glv_mat3* mat);
float glv_mat4_determinant(const glv_mat4* mat);

/* Calculates the cofactor matrix */
glv_mat3 glv_mat3_cofactors(const glv_mat3* mat);
glv_mat4 glv_mat4_cofactors(const glv_mat4* mat);

/* Calculates the inverse matrix */
glv_mat3 glv_mat3_inverse(const glv_mat3* mat);
glv_mat4 glv_mat4_inverse(const glv_mat4* mat);

/* Multiplies two matrices */
glv_mat2 glv_mat2_multiply(const glv_mat2* m1, const glv_mat2* m2);
glv_mat3 glv_mat3_multiply(const glv_mat3* m1, const glv_mat3* m2);
glv_mat4 glv_mat4_multiply(const glv_mat4* m1, const glv_mat4* m2);

/* Multiplies n matrices in series */
glv_mat2 glv_mat2_nmultiply(unsigned int num, ...);
glv_mat3 glv_mat3_nmultiply(unsigned int num, ...);
glv_mat4 glv_mat4_nmultiply(unsigned int num, ...);




/*

glv_mat4 glv_mat4_op(const glv_mat4* mat, int op, float value);
glv_mat4 glv_mat4_func(const glv_mat4* mat, float (*func)(float));

*/

#endif /* GLV_MAT_H */