#include "vfc_loader.h"

#define MAX_GAME_OBJECTS 4096

void writeVFCFile(const char *fileName, GameObject* gameObjects, uint32_t gameObjectCount){
    FILE *file;
    errno_t errorCode;

    errorCode = fopen_s(&file, fileName, "wb");
    if(errorCode != 0){
        fprintf(stderr, "failed to open VFC file!\n");
    }

    VFCHeader header = {
        .vfcMagicByte = "VFC\x00",
        .vfcVersion = 1,
        .vfcFlags = 0,
        .vfcGameObjectCount = gameObjectCount
    };
    fwrite(&header, sizeof(VFCHeader), 1, file);

    for(uint32_t i = 0; i < gameObjectCount; i++){
        fwrite(&gameObjects[i], sizeof(GameObject), 1, file);
    }

    fclose(file);
}

void loadVFCFile(const char *fileName, GameObject** gameObjects, uint32_t* gameObjectCount){
    FILE *file;
    errno_t errorCode;

    errorCode = fopen_s(&file, fileName, "rb");
    if(errorCode != 0){
        fprintf(stderr, "failed to open VFC file!\n");
    }

    VFCHeader header;
    fread(&header, sizeof(VFCHeader), 1, file);

    if(header.vfcMagicByte[0] != 'V' || header.vfcMagicByte[1] != 'F' || header.vfcMagicByte[2] != 'C' || header.vfcMagicByte[3] != '\0'){
        fprintf(stderr, "invalid VFC file: magic byte mismatch\n");
        fclose(file);
        return;
    }

    *gameObjectCount = header.vfcGameObjectCount;
    *gameObjects = (GameObject*)malloc(sizeof(GameObject) * (*gameObjectCount));
    
    fread(*gameObjects, sizeof(GameObject), *gameObjectCount, file);

    fclose(file);
}