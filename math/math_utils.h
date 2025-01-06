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

int clamp(int value, int min, int max);

#endif