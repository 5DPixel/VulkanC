#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "../utils/constants_and_arrays/constants_and_arrays.h"

float generateTerrainHeight(float x, float y);
void createGameObjects(GameObject** objects, uint32_t rowCol);