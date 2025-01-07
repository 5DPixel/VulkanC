#include "math_utils.h"

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void mat4Identity(mat4* matrix){
    for(int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j) {
            matrix->elements[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void mat4Multiply(mat4* result, const mat4* a, const mat4* b) {
    mat4 multiplyResult = { 0 };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            multiplyResult.elements[row][col] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                multiplyResult.elements[row][col] += a->elements[row][k] * b->elements[k][col];
            }
        }
    }

    *result = multiplyResult;
}

void mat4MVPCalculation(mat4* result, const mat4* model, const mat4* view, const mat4* projection){
    mat4 mv;
    mat4_multiply(&mv, model, view);
    mat4_multiply(result, &mv, projection);
}

void mat4Translate(mat4* matrix, vec3 translation){
    mat4Identity(matrix);
    matrix->elements[3][0] = translation.x;
    matrix->elements[3][1] = translation.y;
    matrix->elements[3][2] = translation.z;
}

void mat4Scale(mat4* matrix, vec3 scalar){
    mat4Identity(matrix);
    matrix->elements[0][0] = scalar.x;
    matrix->elements[1][1] = scalar.y;
    matrix->elements[2][2] = scalar.z;
}