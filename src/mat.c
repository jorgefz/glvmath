
#include <stdio.h>
#include <math.h>
#include <stdarg.h>

#include "mat.h"



/* ----- Matrix Creation ----- */

/* Creates 4x4 diagonal matrix */
glv_mat4 glv_mat4_diagonal(float e00, float e11, float e22, float e33){
    unsigned int i;
    float values[] = {e00, e11, e22, e33};
    glv_mat4 m = {0};
    for(i=0; i!=GLV_MAT4_RANK; ++i){
        m.data[i][i] = values[i];
    }
    return m;
}

/* Creates 4x4 identity matrix */
glv_mat4 glv_mat4_identity(){
    return glv_mat4_diagonal(1.0, 1.0, 1.0, 1.0);
}


/* ----- Matrix Operations ----- */
/* Returns the transpose matrix */
glv_mat2 glv_mat2_transpose(const glv_mat2* m){
    glv_mat2 t;
    t.data[0][0] = m->data[0][0];
    t.data[1][1] = m->data[1][1];
    t.data[1][0] = m->data[0][1];
    t.data[0][1] = m->data[1][0];
    return t;
}

glv_mat3 glv_mat3_transpose(const glv_mat3* m){
    glv_mat3 t = {0};
    unsigned int i, j;
    for(i = 0; i != GLV_MAT3_RANK; ++i){
        for(j = 0; j != GLV_MAT3_RANK; ++j){
            t.data[i][j] = m->data[j][i];
        }
    }
    return t;
}

glv_mat4 glv_mat4_transpose(const glv_mat4* m){
    glv_mat4 t = {0};
    unsigned int i, j;
    for(i = 0; i != GLV_MAT4_RANK; ++i){
        for(j = 0; j != GLV_MAT4_RANK; ++j){
            t.data[i][j] = m->data[j][i];
        }
    }
    return t;
}

/* Returns the minor of a matrix at i,j */
float glv_mat3_minor(const glv_mat3* m, unsigned int i,  unsigned int j){
    glv_mat2 subm;
    unsigned int k, l; // input matrix 4x4 indices
    unsigned int a = 0, b = 0; // submatrix 3x3 indices
    for(k = 0; k != GLV_MAT3_RANK; k++){
        if (k == i) continue;
        for(l = 0; l != GLV_MAT3_RANK; l++){
            if (l == j) continue;
            subm.data[a][b] = m->data[k][l];
            b++;
        }
        a++;
        b = 0;
    }
    return glv_mat2_determinant(&subm);
}


float glv_mat4_minor(const glv_mat4* m, unsigned int i,  unsigned int j){
    glv_mat3 subm;
    unsigned int k, l; // input matrix 4x4 indices
    unsigned int a = 0, b = 0; // submatrix 3x3 indices
    for(k = 0; k != GLV_MAT4_RANK; k++){
        if (k == i) continue;
        for(l = 0; l != GLV_MAT4_RANK; l++){
            if (l == j) continue;
            subm.data[a][b] = m->data[k][l];
            b++;
        }
        a++;
        b = 0;
    }
    return glv_mat3_determinant(&subm);
}

/* Returns the determinant of a matrix */
float glv_mat2_determinant(const glv_mat2* m){
    return (m->data[0][0] * m->data[1][1] - m->data[1][0] * m->data[0][1]);
}

float glv_mat3_determinant(const glv_mat3* m){
    float det = 0;
    det += m->data[0][0] * m->data[1][1] * m->data[2][2];
    det += m->data[1][0] * m->data[2][1] * m->data[0][2];
    det += m->data[0][1] * m->data[1][2] * m->data[2][0];
    det -= m->data[0][2] * m->data[1][1] * m->data[2][0];
    det -= m->data[1][0] * m->data[0][1] * m->data[2][2];
    det -= m->data[0][0] * m->data[2][1] * m->data[1][2];
    return det;
}

float glv_mat4_determinant(const glv_mat4* m){
    unsigned int i;
    float sign = 1.0, det = 0.0;
    for(i = 0; i != GLV_MAT4_RANK; ++i){
        det += sign * m->data[0][i] *  glv_mat4_minor(m, 0, i);
        sign *= -1.0;
    }
    return det;
}


/* Returns the cofactor matrix */
glv_mat3 glv_mat3_cofactors(const glv_mat3* m){
    glv_mat3 cof = {0};
    float minor;
    unsigned int i, j;
    for(i = 0; i != GLV_MAT3_RANK; ++i){
        for(j = 0; j != GLV_MAT3_RANK; ++j){
            minor = glv_mat3_minor(m, i, j);
            cof.data[i][j] = powf(-1, i+j) * minor;
        }
    }
    return cof;
}

glv_mat4 glv_mat4_cofactors(const glv_mat4* m){
    glv_mat4 cof = {0};
    float minor;
    unsigned int i, j;
    for(i = 0; i != GLV_MAT4_RANK; ++i){
        for(j = 0; j != GLV_MAT4_RANK; ++j){
            minor = glv_mat4_minor(m, i, j);
            cof.data[i][j] = powf(-1, i+j) * minor;
        }
    }
    return cof;
}

/* Returns the inverse matrix */
glv_mat4 glv_mat4_inverse(const glv_mat4* m){
    glv_mat4 cof, adj, inv;
    float det;
    unsigned int i, j;

    cof = glv_mat4_cofactors(m); // cofactor matrix
    adj = glv_mat4_transpose(&cof); // adjoint matrix
    det = glv_mat4_determinant(m);
    if(det == 0) return (glv_mat4){0}; // non-invertible matrix

    for(i = 0; i != GLV_MAT4_RANK; ++i){
        for(j = 0; j != GLV_MAT4_RANK; ++j){
            inv.data[i][j] = adj.data[i][j] / det;
        }
    }
    return inv;
}


/* Multiplies two matrices */
glv_mat2 glv_mat2_multiply(const glv_mat2* m, const glv_mat2* n){
    glv_mat2 s = {0};
    unsigned int i, j, k;
    for(i = 0; i != GLV_MAT2_RANK; ++i){
        for(j = 0; j != GLV_MAT2_RANK; ++j){
            for(k = 0; k != GLV_MAT2_RANK; ++k){
                s.data[i][j] += m->data[i][k] * n->data[k][j];
            }
        }
    }
    return s;
}

glv_mat3 glv_mat3_multiply(const glv_mat3* m, const glv_mat3* n){
    glv_mat3 s = {0};
    unsigned int i, j, k;
    for(i = 0; i != GLV_MAT3_RANK; ++i){
        for(j = 0; j != GLV_MAT3_RANK; ++j){
            for(k = 0; k != GLV_MAT3_RANK; ++k){
                s.data[i][j] += m->data[i][k] * n->data[k][j];
            }
        }
    }
    return s;
}

glv_mat4 glv_mat4_multiply(const glv_mat4* m, const glv_mat4* n){
    glv_mat4 s = {0};
    unsigned int i, j, k;
    for(i = 0; i != GLV_MAT4_RANK; ++i){
        for(j = 0; j != GLV_MAT4_RANK; ++j){
            for(k = 0; k != GLV_MAT4_RANK; ++k){
                s.data[i][j] += m->data[i][k] * n->data[k][j];
            }
        }
    }
    return s;
}

/* Multiplies n matrices in series */
glv_mat2 glv_mat2_nmultiply(unsigned int len, ...){
    if(len == 0) return (glv_mat2){0};
    va_list args;
    va_start(args, len);
    glv_mat2 *m, *n;
    m = va_arg(args, glv_mat2*);
    if(len == 1){
        va_end(args);
        return *m;
    }
    unsigned int i;
    for(i = 1; i != len; ++i){
        n = va_arg(args, glv_mat2*);
        *m = glv_mat2_multiply(m, n);
    }
    va_end(args);
    return *m;
}

glv_mat3 glv_mat3_nmultiply(unsigned int len, ...){
    if(len == 0) return (glv_mat3){0};
    va_list args;
    va_start(args, len);
    glv_mat3 *m, *n;
    m = va_arg(args, glv_mat3*);
    if(len == 1){
        va_end(args);
        return *m;
    }
    unsigned int i;
    for(i = 1; i != len; ++i){
        n = va_arg(args, glv_mat3*);
        *m = glv_mat3_multiply(m, n);
    }
    va_end(args);
    return *m;
}

glv_mat4 glv_mat4_nmultiply(unsigned int len, ...){
    if(len == 0) return (glv_mat4){0};
    va_list args;
    va_start(args, len);
    glv_mat4 *m, *n;
    m = va_arg(args, glv_mat4*);
    if(len == 1){
        va_end(args);
        return *m;
    }
    unsigned int i;
    for(i = 1; i != len; ++i){
        n = va_arg(args, glv_mat4*);
        *m = glv_mat4_multiply(m, n);
    }
    va_end(args);
    return *m;
}



