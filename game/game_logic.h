#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../utils/constants_and_arrays/constants_and_arrays.h"
#include "../math/noise.h"

float generateTerrainHeight(float x, float y, long seed);
void createGameObjects(GameObject** objects, uint32_t rowCol, long seed);