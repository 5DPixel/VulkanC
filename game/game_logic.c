#include "game_logic.h"

void createGameObjects(GameObject** objects, uint32_t rowCol){
    *objects = (GameObject*)malloc(rowCol * rowCol * sizeof(GameObject));

    for(uint32_t i = 0; i < rowCol; i++){
        for(uint32_t j = 0; j < rowCol; j++){
            (*objects)[i * rowCol + j].position = (vec3){i * 2.0f , j * 2.0f, 0.0f};
            (*objects)[i * rowCol + j].scale = (vec3){0.3f, 0.3f, 0.3f};
            (*objects)[i * rowCol + j].rotation = (vec3){0.0f, 0.0f, 0.0f};
        }
    }
}