#pragma once
#include <stdio.h>
#include <string.h>
#include "../utils/constants_and_arrays/constants_and_arrays.h"
#include <stdlib.h>
#include <ctype.h>
#include "../math/hash_map.h"

void loadOBJ(const char* filePath, Vertex** vertices, uint32_t* vertexCount, uint32_t** indices, uint32_t* indexCount);