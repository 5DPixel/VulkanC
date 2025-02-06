#pragma once

#include <math.h>

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
    float m[4][4];
} mat4;

#define PI 3.14159265358979323846

int clamp(int value, int min, int max);
float deg2Rad(float degrees);

//Vector functions
vec3 normalize(vec3 vector);
vec3 cross(vec3 a, vec3 b);
vec3 add(vec3 a, vec3 b);
vec3 subtract(vec3 a, vec3 b);
vec3 scale(vec3 vector, float scalar);
float dot(vec3 a, vec3 b);
float lerp(float start, float end, float t);
float easeInOutQuad(float t);
float easeInOutSine(float t);
float smoothInterpolate(float x, float y, float s);

//Matrix functions
mat4 mat4Identity();
mat4 mat4Multiply(const mat4 a, const mat4 b);
mat4 mat4MVPCalculation(const mat4 model, const mat4 view, const mat4 projection);
mat4 mat4Translate(mat4 matrix, vec3 translation);
mat4 mat4Scale(mat4 matrix, vec3 scalar);
mat4 mat4RotateX(mat4 matrix, float angle);
mat4 mat4RotateY(mat4 matrix, float angle);
mat4 mat4RotateZ(mat4 matrix, float angle);
mat4 mat4RotateEuler(mat4 matrix, vec3 rotation);
mat4 mat4LookAt(vec3 eye, vec3 center, vec3 up);
mat4 mat4Perspective(float fov, float aspect, float near, float far);