#include "game_logic.h"

float generateTerrainHeight(float x, float y, long seed){
    float height = perlin2DOctaves(x, y, 0.5f, 12.0f, 32, seed);

    return height;
}

void createGameObjects(GameObject** objects, uint32_t rowCol, long seed){
    printf("Generated world seed: %d\n", seed);
    *objects = (GameObject*)malloc(rowCol * rowCol * sizeof(GameObject));

    float amplitude = 1.5f;

    for(uint32_t i = 0; i < rowCol; i++){
        for(uint32_t j = 0; j < rowCol; j++){
            float x = (float)i / rowCol * 10.0f;
            float y = (float)j / rowCol * 10.0f;

            float z = amplitude * generateTerrainHeight(x, y, seed);

            z = roundf(z / 2.0f) * 2.0f;

            (*objects)[i * rowCol + j].position = (vec3){i * 2.0f , j * 2.0f, z - 25.0f};
            (*objects)[i * rowCol + j].scale = (vec3){0.3f, 0.3f, 0.3f};
            (*objects)[i * rowCol + j].rotation = (vec3){0.0f, 0.0f, 0.0f};
        }
    }
}