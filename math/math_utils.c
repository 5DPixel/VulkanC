#include "math_utils.h"

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

//Vector functions
vec3 normalize(vec3 vector){
    float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

    if(magnitude == 0){
        return vector;
    }
    
    vec3 normalized;
    normalized.x = vector.x / magnitude;
    normalized.y = vector.y / magnitude;
    normalized.z = vector.z / magnitude;

    return normalized;
}

mat4 mat4Identity(){
    mat4 matrix = {0};

    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;

    return matrix;
}

mat4 mat4Multiply(const mat4 a, const mat4 b) {
    mat4 multiplyResult = { 0 };

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            multiplyResult.m[row][col] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                multiplyResult.m[row][col] += a.m[row][k] * b.m[k][col];
            }
        }
    }

    return multiplyResult;
}

mat4 mat4MVPCalculation(const mat4 model, const mat4 view, const mat4 projection){
    mat4 mv = mat4Multiply(model, view);
    mat4 result = mat4Multiply(mv, projection);

    return result;
}

mat4 mat4Translate(mat4 matrix, vec3 translation){
    mat4Identity(matrix);
    matrix.m[3][0] = translation.x;
    matrix.m[3][1] = translation.y;
    matrix.m[3][2] = translation.z;

    return matrix;
}

mat4 mat4Scale(mat4 matrix, vec3 scalar){
    mat4Identity(matrix);
    matrix.m[0][0] = scalar.x;
    matrix.m[1][1] = scalar.y;
    matrix.m[2][2] = scalar.z;

    return matrix;
}

mat4 mat4RotateX(mat4 matrix, float angle) {
    matrix.m[0][0] = 1;
    matrix.m[1][1] = cosf(angle);
    matrix.m[1][2] = -sinf(angle);
    matrix.m[2][1] = sinf(angle);
    matrix.m[2][2] = cosf(angle);
    matrix.m[3][3] = 1;

    return matrix;
}

mat4 mat4RotateY(mat4 matrix, float angle){
    matrix.m[0][0] = cosf(angle);
    matrix.m[0][2] = sinf(angle);
    matrix.m[2][0] = -sinf(angle);
    matrix.m[1][1] = 1;
    matrix.m[2][2] = cosf(angle);
    matrix.m[3][3] = 1;

    return matrix;
}

mat4 mat4RotateZ(mat4 matrix, float angle){
    matrix.m[0][0] = cosf(angle);
    matrix.m[0][1] = -sinf(angle);
    matrix.m[1][0] = sinf(angle);
    matrix.m[1][1] = cosf(angle);
    matrix.m[2][2] = 1;
    matrix.m[3][3] = 1;

    return matrix;
}