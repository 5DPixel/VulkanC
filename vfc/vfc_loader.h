#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../utils/constants_and_arrays/constants_and_arrays.h"

typedef struct {
    char vfcMagicByte[4];
    uint16_t vfcVersion;
    uint16_t vfcFlags;
    uint32_t vfcGameObjectCount;
    uint32_t vfcCompressedSize;
    uint32_t vfcUncompressedSize;
    vec2 regionPosition;
} VFCHeader;

typedef struct {
    char vfmMagicByte[4];
    uint16_t vfmVersion;
    uint16_t vfmFlags;
    uint32_t vfmRegionCount;
    uint32_t vfmCompressedSize;
    uint32_t vfmUncompressedSize;
} VFMHeader;

typedef struct {
    uint32_t entryLength;
    char* entryName;
} VFMRegionEntry;

void writeVFCRegion(const char *regionDirectory, GameObject* gameObjects, uint32_t gameObjectCount, vec2 regionPosition);
void loadVFCRegion(const char *regionDirectory, vec2 regionPosition, GameObject** gameObjects, uint32_t* gameObjectCount, VFCHeader* outHeader);
char** loadVFMFile(const char* vfmFileName, uint32_t *outRegionCount);