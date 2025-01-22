#pragma once

#include "../utils/constants_and_arrays/constants_and_arrays.h"
#include <string.h>
#include <stdio.h>

typedef struct {
    Vertex key;
    uint32_t value;
} vertexHashMapItem;

vertexHashMapItem* linearSearch(vertexHashMapItem* items, size_t size, const Vertex key);