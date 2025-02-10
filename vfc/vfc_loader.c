#include "vfc_loader.h"

#define MINIZ_IMPL
#include "../zlib/miniz.h"

#define MAX_GAME_OBJECTS 9216

void writeVFCRegion(const char *regionDirectory, GameObject* gameObjects, uint32_t gameObjectCount, vec2 regionPosition){
    FILE *file;
    errno_t errorCode;

    char x[10];
    char y[10];

    itoa(regionPosition.x, x, 10);
    itoa(regionPosition.y, y, 10);

    char fileName[150];

    sprintf(fileName, "%s/regions/r-%s-%s.vfc", regionDirectory, x, y);

    errorCode = fopen_s(&file, fileName, "wb");
    if(errorCode != 0){
        fprintf(stderr, "failed to open VFC file!\n");
    }

    uint32_t uncompressedSize = sizeof(GameObject) * gameObjectCount;
    uint32_t compressedSize = mz_compressBound(uncompressedSize);
    void* compressedData = malloc(compressedSize);

    if(!compressedData){
        fprintf(stderr, "failed to allocate memory for compression!\n");
        fclose(file);
        
        return;
    }

    int result = mz_compress((unsigned char*)compressedData, &compressedSize, (unsigned char*)gameObjects, uncompressedSize);

    if(result != MZ_OK){
        fprintf(stderr, "compression failed!\n");
        free(compressedData);
        fclose(file);
        return;
    }

    VFCHeader header = {
        .vfcMagicByte = "VFC\x00",
        .vfcVersion = CURRENT_VFC_VERSION,
        .vfcFlags = 0,
        .vfcGameObjectCount = gameObjectCount,
        .vfcCompressedSize = compressedSize,
        .vfcUncompressedSize = uncompressedSize,
        .regionPosition = regionPosition
    };
    fwrite(&header, sizeof(VFCHeader), 1, file);

    fwrite(compressedData, 1, compressedSize, file);

    fclose(file);

    FILE *vfmFile;

    char vfmFileName[150];
    errno_t vfmFileErrorCode;
    sprintf(vfmFileName, "%s/regions/regions.vfm", regionDirectory);

    vfmFileErrorCode = fopen_s(&vfmFile, vfmFileName, "a");
    if(vfmFileErrorCode != 0){
        fprintf(stderr, "failed to open vfm file!");
        free(compressedData);
        return;
    }

    fprintf(vfmFile, "r-%s-%s.vfc\n", x, y);

    fclose(vfmFile);

    free(compressedData);
}

void loadVFCRegion(const char *regionDirectory, vec2 regionPosition, GameObject** gameObjects, uint32_t* gameObjectCount, VFCHeader* outHeader){
    FILE *file;
    errno_t errorCode;

    char x[10];
    char y[10];

    itoa(regionPosition.x, x, 10);
    itoa(regionPosition.y, y, 10);

    char fullFileName[150];

    sprintf(fullFileName, "%s/regions/r-%s-%s.vfc", regionDirectory, x, y);

    errorCode = fopen_s(&file, fullFileName, "rb");
    if(errorCode != 0){
        fprintf(stderr, "failed to open VFC file!\n");
        return;
    }

    VFCHeader header;
    fread(&header, sizeof(VFCHeader), 1, file);

    if(header.vfcMagicByte[0] != 'V' || header.vfcMagicByte[1] != 'F' || header.vfcMagicByte[2] != 'C' || header.vfcMagicByte[3] != '\0'){
        fprintf(stderr, "invalid VFC file: magic byte mismatch\n");
        fclose(file);
        return;
    }

    regionPosition.x = header.regionPosition.x;
    regionPosition.y = header.regionPosition.y;

    *gameObjectCount = header.vfcGameObjectCount;

    void* compressedData = malloc(header.vfcCompressedSize);
    if (!compressedData) {
        fprintf(stderr, "failed to allocate memory for compressed data!\n");
        fclose(file);
        return;
    }

    fread(compressedData, 1, header.vfcCompressedSize, file);
    fclose(file);

    *gameObjects = (GameObject*)malloc(header.vfcUncompressedSize);
    if (!*gameObjects) {
        fprintf(stderr, "failed to allocate memory for decompression!\n");
        free(compressedData);
        return;
    }

    uint32_t uncompressedSize = header.vfcUncompressedSize;
    int result = mz_uncompress((unsigned char*)*gameObjects, &uncompressedSize, 
                               (unsigned char*)compressedData, header.vfcCompressedSize);

    free(compressedData);

    if (result != MZ_OK || uncompressedSize != header.vfcUncompressedSize) {
        fprintf(stderr, "decompression failed!\n");
        free(*gameObjects);
        *gameObjects = NULL;
        return;
    }

    fclose(file);
}

char** loadVFMFile(const char* vfmFileName, uint32_t *outRegionCount){
    FILE *vfmFile;
    fopen_s(&vfmFile, vfmFileName, "r");
    if (!vfmFile) {
        fprintf(stderr, "failed to open VFM file!\n");
        return NULL;
    }

    uint32_t regionCount = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), vfmFile)) {
        regionCount++;
    }

    fseek(vfmFile, 0, SEEK_SET);

    char **regionFileNames = (char**)malloc(regionCount * sizeof(char*));
    if (!regionFileNames) {
        fprintf(stderr, "failed to allocate memory for region file names!\n");
        fclose(vfmFile);
        return NULL;
    }

    uint32_t index = 0;
    while (fgets(buffer, sizeof(buffer), vfmFile)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        regionFileNames[index] = (char*)malloc(strlen(buffer) + 1);
        if (!regionFileNames[index]) {
            fprintf(stderr, "failed to allocate memory for file name!\n");
            for (uint32_t i = 0; i < index; i++) {
                free(regionFileNames[i]);
            }
            free(regionFileNames);
            fclose(vfmFile);
            return NULL;
        }

        strcpy(regionFileNames[index], buffer);
        index++;
    }

    *outRegionCount = regionCount;

    fclose(vfmFile);
    return regionFileNames;
}