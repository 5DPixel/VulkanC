#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../utils/constants_and_arrays/constants_and_arrays.h"
#include "../math/noise.h"
#include "../vfc/vfc_loader.h"

float generateTerrainHeight(float x, float y, long seed);
void createGameObjects(GameObject** objects, uint32_t chunks, long seed, const char* regionDirectory);
void createChunk(GameObject** objects, uint32_t rowCol, long seed, float x, float y, uint32_t chunkIndexX, uint32_t chunkIndexY);
void loadGameObjects(GameObject** objects, uint32_t chunks, long seed, const char* regionDirectory);
vec3 getSkyColor(int tick);
float getSkyAmbient(int tick);