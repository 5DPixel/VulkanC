#ifndef MATH_UTILS_H
#define MATH_UTILS_H

//Structs
typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float elements[4][4];
} mat4;

int clamp(int value, int min, int max);
void mat4Identity(mat4* matrix);
void mat4Multiply(mat4* result, const mat4* a, const mat4* b);
void mat4MVPCalculation(mat4* result, const mat4* model, const mat4* view, const mat4* projection);
void mat4Translate(mat4* matrix, vec3 translation);
void mat4Scale(mat4* matrix, vec3 scalar);

#endif