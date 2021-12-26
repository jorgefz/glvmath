
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/glvmath.h"

//GLV_VEC2__DECL(double) glv_dvec2;

glv_mat4 camera(float translate, const glv_vec2* rotate){

    glv_mat4 identity = glv_mat4_identity();
	glv_mat4 projection = glv_perspective(M_PI * 0.25f, 4.0f / 3.0f, 0.1f, 100.0f);
	glv_mat4 view = glv_translate(&identity, &(glv_vec3){.x=0.0f, .y=0.0f, .z=-translate} );
	view = glv_rotate(&view, rotate->y, &(glv_vec3){.x=-1.0f, .y=0.0f, .z=0.0f});
	view = glv_rotate(&view, rotate->x, &(glv_vec3){.x=0.0f, .y=1.0f, .z=0.0f});
	glv_mat4 model = glv_scale(&identity, &(glv_vec3){.x=0.5f, .y=0.5f, .z=0.5f});

	return glv_mat4_nmultiply(3, &projection, &view, &model);
}


void mat4print(glv_mat4* m){
    unsigned int i, j;
    for(i=0; i!=4; ++i){
        printf("| ");
        for(j=0; j!=4; ++j){
            printf("%6.3f ", m->data[i][j]);
        }
        printf(" |\n");
    }
}

void mat3print(glv_mat3* m){
    unsigned int i, j;
    for(i=0; i!=3; ++i){
        printf("| ");
        for(j=0; j!=3; ++j){
            printf("%6.3f ", m->data[i][j]);
        }
        printf(" |\n");
    }
}

void mat2print(glv_mat2* m){
    unsigned int i, j;
    for(i=0; i!=2; ++i){
        printf("| ");
        for(j=0; j!=2; ++j){
            printf("%6.3f ", m->data[i][j]);
        }
        printf(" |\n");
    }
}

void testing_mat2(){
    printf("\n--- 2x2 Matrix Testing ---\n");
    glv_mat2 m = {.data={{1.0,2.0},{3.0,4.0}}};
    mat2print(&m);

    printf("Transpose twice:\n");
    m = glv_mat2_transpose(&m);
    m = glv_mat2_transpose(&m);
    mat2print(&m);

    printf("Determinant: %f\n", glv_mat2_determinant(&m));

    printf("Multiplication:\n");
    glv_mat2 a = m, b, c;
    b = (glv_mat2){.data={{4.0,3.0},{2.0,1.0}}};
    c = glv_mat2_multiply(&a, &b);
    printf(" > A = \n");
    mat2print(&a);
    printf(" > B = \n");
    mat2print(&b);
    printf(" > A x B = \n");
    mat2print(&c);

    printf(" Multiply in series:\n");
    printf(" > A x B x (A x B)\n");
    c = glv_mat2_nmultiply(3, &a, &b, &c);
    mat2print(&c);
}


void testing_mat3(){
    printf("\n--- 3x3 Matrix Testing ---\n");
    glv_mat3 m = {.data={{1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}}};
    mat3print(&m);
    
    printf("Transpose twice:\n");
    m = glv_mat3_transpose(&m);
    m = glv_mat3_transpose(&m);
    mat3print(&m);

    printf("Determinant: %f\n", glv_mat3_determinant(&m));

    printf("Multiplication:\n");
    glv_mat3 a = m, b, c;
    b = (glv_mat3){.data={{9.0,8.0,7.0},{6.0,5.0,4.0},{3.0,2.0,1.0}}};
    c = glv_mat3_multiply(&a, &b);
    printf(" > A = \n");
    mat3print(&a);
    printf(" > B = \n");
    mat3print(&b);
    printf(" > A x B = \n");
    mat3print(&c);
}

void testing_mat4(){
    printf("\n--- 4x4 Matrix Testing ---\n");
    glv_mat4 m;
    
    printf("Identity matrix:\n");
    m = glv_mat4_identity();
    mat4print(&m);

    printf("Diagonal matrix:\n");
    m = glv_mat4_diagonal(-5.0f, -5.0f, -5.0f, 1.0f);
    mat4print(&m);

    printf("Orthographic matrix:\n");
    m = glv_ortho(0.0, 5.0, 0.0, 5.0, 0.1f, 100.0f);
    mat4print(&m);

    printf("Rotate matrix:\n");
    m = glv_rotate(&m, 0.5f, &(glv_vec3){.x=0.2f, .y=0.15f, .z=0.1f});
    mat4print(&m);

    printf("Transpose twice (should be unchanged)\n");
    m = glv_mat4_transpose(&m);
    m = glv_mat4_transpose(&m);
    mat4print(&m);

    printf("Determinant: %f\n", glv_mat4_determinant(&m));

    printf("Multiplication:\n");
    glv_mat4 a, b, c;
    b = (glv_mat4){.data={
        {1.0,  15.0, 14.0, 13.0},
        {12.0, -1.0, 10.0, 9.0},
        {8.0,  7.0,  4.0,  5.0},
        {4.0,  3.0,  2.0,  1.0}
    }};
    a = glv_mat4_transpose(&b);
    c = glv_mat4_multiply(&a, &b);
    printf(" > A = \n");
    mat4print(&a);
    printf(" > B = \n");
    mat4print(&b);
    printf(" > A x B = \n");
    mat4print(&c);

    printf("Original x Inverse: Identity\n");
    glv_mat4 inv = glv_mat4_inverse(&a);
    glv_mat4 idn = glv_mat4_multiply(&a, &inv);
    mat4print(&idn);
}


void testing_vec(){
    printf("--- Vector Testing ---\n");
    glv_vec4 color = {.r = 0.5, .g = 0.5, .b = 0.5, .a = 1.0};
    printf("Some vector: ");
    for(int i=0; i!=GLV_VEC4_LEN; ++i){
        printf("%f ", color.data[i]);
    }
    printf("\n");

    printf("Magnitude: %f\n", glv_vec4_magnitude(&color));
    glv_vec4 norm = glv_vec4_normalize(&color);
    printf("Normalized: %f %f %f %f\n", norm.r, norm.g, norm.b, norm.a);
    printf("Magnitude should now be unity: %f\n", glv_vec4_magnitude(&norm));

    glv_vec3 a = {.x=norm.x, .y=norm.y, .z=norm.z};
    glv_vec3 b = {.x=color.x/2, .y=color.y*4, .z=color.z-1};
    printf("Dot product norm3d * orig3d: %f\n", glv_vec3_dot(&a, &b));
    glv_vec3 cross = glv_vec3_cross(&a, &b);
    printf("Cross product norm x orig: %f %f %f\n", cross.x, cross.y, cross.z);

}

int main(){
    
    testing_vec();
    
    testing_mat4();
    testing_mat3();
    testing_mat2();

    return 0;
}


