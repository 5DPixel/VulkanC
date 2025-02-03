#pragma once

#include "../utils/constants_and_arrays/constants_and_arrays.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    Vertex key;
    uint32_t value;
} vertexHashMapItem;

vertexHashMapItem* binarySearch(vertexHashMapItem* items, uint32_t size, const Vertex key);
vertexHashMapItem* deduplicateVertices(vertexHashMapItem* items, uint32_t size, uint32_t* newSize);
vertexHashMapItem* createVertexHashMap(Vertex* vertices, uint32_t size);