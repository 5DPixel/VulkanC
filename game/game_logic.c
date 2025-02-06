#include "game_logic.h"

float generateTerrainHeight(float x, float y) {
    float height = 2.5f * sinf(x * 0.5f) * cosf(y * 0.5f);
    height += 1.5f * sinf(x * 0.2f) * cosf(y * 0.2f);
    height += 0.5f * sinf(x * 1.0f + y * 1.0f);

    float radius = sqrtf(x * x + y * y);
    height += 1.0f * sinf(radius * 0.3f);

    return height;
}

void createGameObjects(GameObject** objects, uint32_t rowCol){
    *objects = (GameObject*)malloc(rowCol * rowCol * sizeof(GameObject));

    float amplitude = 2.0f;
    float frequency = 0.5f;

    for(uint32_t i = 0; i < rowCol; i++){
        for(uint32_t j = 0; j < rowCol; j++){
            float x = (float)i / rowCol * 10.0f;
            float y = (float)j / rowCol * 10.0f;

            float z = amplitude * generateTerrainHeight(x, y);

            z = roundf(z / 2.0f) * 2.0f;

            (*objects)[i * rowCol + j].position = (vec3){i * 2.0f , j * 2.0f, z};
            (*objects)[i * rowCol + j].scale = (vec3){0.3f, 0.3f, 0.3f};
            (*objects)[i * rowCol + j].rotation = (vec3){0.0f, 0.0f, 0.0f};
        }
    }
}