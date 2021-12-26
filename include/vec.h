
/*
    === vec.h ===
    Implementation of OpenGL Shading language (GLSL) vectors.

    Type names are 'glv_' followed by:
        float   int     unsigned int
    2D  fvec2   ivec2   uvec2
    3D  fvec3   ivec3   uvec3
    4D  fvec4   ivec4   uvec4
    
    Members:
        xyzw for position
        stuv for textures
        rgba for color

    Access to data as contiguous array with: vec.data

    Vectors which contain other data types can be declared
    with the following macros:
        GLV_VEC2__DECL(type) typename;
        GLV_VEC3__DECL(type) typename;
        GLV_VEC4__DECL(type) typename;

    Example:
        glv_fvec4 color = {.r=0.5, .g=0.5, .b=0.1, .a=1.0};
        for(int i=0; i!=GLV_VEC4_LEN; ++i){
            printf("%f\n", color.data[i]);
        }

        glv_fvec2 pos = {.x = 4.0, .y = 5.0};
        float distance = sqrt( pos.x*pos.x + pos.y*pos.y );
*/


#ifndef GLV_VEC_H
#define GLV_VEC_H 1

#define GLV_VEC2_LEN 2
#define GLV_VEC3_LEN 3
#define GLV_VEC4_LEN 4

/* Macro that declares vec2 of given type T */ 
#define GLV_VEC2__DECL(T)       \
typedef union {                 \
    T data[GLV_VEC2_LEN];       \
    struct{                     \
        union { T x; T s; };    \
        union { T y; T t; };    \
    };                          \
}

/* Macro that declares vec3 of given type T */ 
#define GLV_VEC3__DECL(T)       \
typedef union {                 \
    T data[GLV_VEC3_LEN];       \
    struct{                     \
        union { T x; T s; T r; };\
        union { T y; T t; T g; };\
        union { T z; T u; T b; };\
    };                          \
}

/* Macro that declares vec4 of given type T */ 
#define GLV_VEC4__DECL(T)       \
typedef union {                 \
    T data[GLV_VEC4_LEN];       \
    struct{                     \
        union { T x; T s; T r; };\
        union { T y; T t; T g; };\
        union { T z; T u; T b; };\
        union { T w; T v; T a; };\
    };                          \
}

/* Predefined vec types */
GLV_VEC2__DECL(float) glv_fvec2;
GLV_VEC3__DECL(float) glv_fvec3;
GLV_VEC4__DECL(float) glv_fvec4;

GLV_VEC2__DECL(int) glv_ivec2;
GLV_VEC3__DECL(int) glv_ivec3;
GLV_VEC4__DECL(int) glv_ivec4;

GLV_VEC2__DECL(unsigned int) glv_uvec2;
GLV_VEC3__DECL(unsigned int) glv_uvec3;
GLV_VEC4__DECL(unsigned int) glv_uvec4;

typedef glv_fvec2 glv_vec2;
typedef glv_fvec3 glv_vec3;
typedef glv_fvec4 glv_vec4;

/*
    Function Declarations
*/
/* Returns the length of the vector */
float glv_vec2_magnitude(const glv_vec2* v);
float glv_vec3_magnitude(const glv_vec3* v);
float glv_vec4_magnitude(const glv_vec4* v);

/* Scales the vector to have length of 1 */
glv_vec2 glv_vec2_normalize(const glv_vec2* v);
glv_vec3 glv_vec3_normalize(const glv_vec3* v);
glv_vec4 glv_vec4_normalize(const glv_vec4* v);

/* Calculates dot product */
float glv_vec2_dot(const glv_vec2* v1, const glv_vec2* v2);
float glv_vec3_dot(const glv_vec3* v1, const glv_vec3* v2);
float glv_vec4_dot(const glv_vec4* v1, const glv_vec4* v2);

/* Calculates cross product */
glv_vec3 glv_vec3_cross(const glv_vec3* v1, const glv_vec3* v2);



#endif /* GLV_VEC_H */

