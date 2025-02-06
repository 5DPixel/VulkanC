#include "math_utils.h"

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float deg2Rad(float degrees){
    return degrees * (PI / 180.0f);
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

vec3 add(vec3 a, vec3 b){
    return (vec3){
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

vec3 scale(vec3 vector, float scalar) {
    return (vec3){
        vector.x * scalar,
        vector.y * scalar,
        vector.z * scalar
    };
}

vec3 cross(vec3 a, vec3 b){
    return (vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

vec3 subtract(vec3 a, vec3 b){
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

float dot(vec3 a, vec3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

float easeInOutQuad(float t) {
    return t < 0.5f ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

float easeInOutSine(float t) {
    return -0.5f * (cosf(PI * t) - 1.0f);
}

float smoothInterpolate(float x, float y, float s){
    return lerp(x, y, s * s * (3 - 2 * s));
}

float distance(vec3 a, vec3 b) {
    return sqrtf((b.x - a.x) * (b.x - a.x) + 
                 (b.y - a.y) * (b.y - a.y) + 
                 (b.z - a.z) * (b.z - a.z));
}

int checkAABBIntersection(vec3 rayOrigin, vec3 rayDir, vec3 aabbMin, vec3 aabbMax) {
    float tMin = (aabbMin.x - rayOrigin.x) / rayDir.x;
    float tMax = (aabbMax.x - rayOrigin.x) / rayDir.x;

    if (tMin > tMax) {
        float temp = tMin;
        tMin = tMax;
        tMax = temp;
    }

    float tyMin = (aabbMin.y - rayOrigin.y) / rayDir.y;
    float tyMax = (aabbMax.y - rayOrigin.y) / rayDir.y;

    if (tyMin > tyMax) {
        float temp = tyMin;
        tyMin = tyMax;
        tyMax = temp;
    }

    if ((tMin > tyMax) || (tyMin > tMax)) {
        return 0; // No intersection
    }

    if (tyMin > tMin) tMin = tyMin;
    if (tyMax < tMax) tMax = tyMax;

    float tzMin = (aabbMin.z - rayOrigin.z) / rayDir.z;
    float tzMax = (aabbMax.z - rayOrigin.z) / rayDir.z;

    if (tzMin > tzMax) {
        float temp = tzMin;
        tzMin = tzMax;
        tzMax = temp;
    }

    if ((tMin > tzMax) || (tzMin > tMax)) {
        return 0; // No intersection
    }

    if (tzMin > tMin) tMin = tzMin;
    if (tzMax < tMax) tMax = tzMax;

    return 1; // Intersection
}

//Matrix functions

mat4 mat4Identity(){
    mat4 matrix = {0};

    matrix.m[0][0] = 1.0f;
    matrix.m[1][1] = 1.0f;
    matrix.m[2][2] = 1.0f;
    matrix.m[3][3] = 1.0f;

    return matrix;
}

mat4 mat4Multiply(const mat4 a, const mat4 b){
    mat4 multiplyResult = mat4Identity();

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
    mat4 pv = mat4Multiply(projection, view);
    mat4 result = mat4Multiply(pv, model);

    return result;
}

mat4 mat4Translate(mat4 matrix, vec3 translation){
    matrix.m[3][0] = translation.x;
    matrix.m[3][1] = translation.y;
    matrix.m[3][2] = translation.z;

    return matrix;
}

mat4 mat4Scale(mat4 matrix, vec3 scalar){
    matrix.m[0][0] = scalar.x;
    matrix.m[1][1] = scalar.y;
    matrix.m[2][2] = scalar.z;

    return matrix;
}

mat4 mat4RotateX(mat4 matrix, float angle){
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

mat4 mat4RotateZ(mat4 matrix, float angle) {
    matrix.m[0][0] = cosf(angle);
    matrix.m[0][1] = -sinf(angle);
    matrix.m[1][0] = sinf(angle);
    matrix.m[1][1] = cosf(angle);
    
    matrix.m[2][0] = 0;
    matrix.m[2][1] = 0;
    matrix.m[2][2] = 1;
    matrix.m[2][3] = 0;
    
    matrix.m[3][0] = 0;
    matrix.m[3][1] = 0;
    matrix.m[3][2] = 0;
    matrix.m[3][3] = 1;

    return matrix;
}

mat4 mat4RotateEuler(mat4 matrix, vec3 rotation){
    mat4 rx = mat4RotateX(matrix, rotation.x);
    mat4 ry = mat4RotateY(matrix, rotation.y);
    mat4 rz = mat4RotateZ(matrix, rotation.z);

    mat4 r = mat4Multiply(mat4Multiply(rz, ry), rx);
    return r;
}

mat4 mat4LookAt(vec3 eye, vec3 center, vec3 up){
    vec3 f = normalize(subtract(center, eye));
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);

    mat4 result = mat4Identity();

    result.m[0][0] = s.x; result.m[1][0] = s.y; result.m[2][0] = s.z; result.m[3][0] = 0.0f;
    result.m[0][1] = u.x; result.m[1][1] = u.y; result.m[2][1] = u.z; result.m[3][1] = 0.0f;
    result.m[0][2] = -f.x; result.m[1][2] = -f.y; result.m[2][2] = -f.z; result.m[3][2] = 0.0f;
    result.m[0][3] = 0.0f; result.m[1][3] = 0.0f; result.m[2][3] = 0.0f; result.m[3][3] = 1.0f;

    result.m[3][0] = -dot(s, eye);
    result.m[3][1] = -dot(u, eye);
    result.m[3][2] = dot(f, eye);

    return result;
}

mat4 mat4Perspective(float fov, float aspect, float near, float far) {
    mat4 result = {0};

    float tanHalfFov = tanf(fov / 2.0f);

    result.m[0][0] = 1.0f / (aspect * tanHalfFov);
    result.m[1][0] = 0.0f;
    result.m[2][0] = 0.0f;
    result.m[3][0] = 0.0f;

    result.m[0][1] = 0.0f;
    result.m[1][1] = -1.0f / tanHalfFov;
    result.m[2][1] = 0.0f;
    result.m[3][1] = 0.0f;

    result.m[0][2] = 0.0f;
    result.m[1][2] = 0.0f;
    result.m[2][2] = far / (near - far);
    result.m[3][2] = (far * near) / (near - far);

    result.m[0][3] = 0.0f;
    result.m[1][3] = 0.0f;
    result.m[2][3] = -1.0f;
    result.m[3][3] = 0.0f;

    return result;
}