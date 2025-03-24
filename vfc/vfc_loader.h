#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../utils/constants_and_arrays/constants_and_arrays.h"

#define CURRENT_VFC_VERSION MAKE_VERSION(1, 0, 0)
#define CURRENT_VFC_VERSION_STRING "1.0.0"

typedef struct {
    char vfcMagicByte[4];
    uint16_t vfcVersion;
    uint16_t vfcFlags;
    uint32_t vfcGameObjectCount;
    uint32_t vfcCompressedSize;
    uint32_t vfcUncompressedSize;
    vec2 regionPosition;
} VFCHeader;

void writeVFCRegion(const char *regionDirectory, GameObject* gameObjects, uint32_t gameObjectCount, vec2 regionPosition);
void loadVFCRegion(const char *regionDirectory, vec2 regionPosition, GameObject** gameObjects, uint32_t* gameObjectCount, VFCHeader* outHeader);
void writeVFMFile(const char *regionDirectory);
char** loadVFMFile(const char* vfmFileName, uint32_t *outRegionCount);