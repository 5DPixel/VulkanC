#pragma once

#include <stdio.h>

#include "../utils/constants_and_arrays/constants_and_arrays.h"

typedef struct {
    char vfcMagicByte[4];
    uint16_t vfcVersion;
    uint16_t vfcFlags;
    uint32_t vfcGameObjectCount;
} VFCHeader;

void writeVFCFile(const char *fileName, GameObject* gameObjects, uint32_t gameObjectCount);
void loadVFCFile(const char *fileName, GameObject** gameObjects, uint32_t gameObjectCount);