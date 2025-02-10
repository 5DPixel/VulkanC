#include "game_logic.h"

float generateTerrainHeight(float x, float y, long seed){
    float height = perlin2DOctaves(x, y, 0.1f, 1.0f, 64, seed);

    return height;
}

void createChunk(GameObject** objects, uint32_t rowCol, long seed, float x, float y, uint32_t chunkIndexX, uint32_t chunkIndexY){
    *objects = (GameObject*)malloc(rowCol * rowCol * sizeof(GameObject));

    float amplitude = 2.0f;

    float scale = 1.0f;

    float offsetX = chunkIndexX * rowCol * scale;
    float offsetY = chunkIndexY * rowCol * scale;

    for(uint32_t i = 0; i < rowCol; i++){
        for(uint32_t j = 0; j < rowCol; j++){
            float x1 = (float)i / rowCol * 10.0f + offsetX;
            float y1 = (float)j / rowCol * 10.0f + offsetY;

            float z = amplitude * generateTerrainHeight(x1, y1, seed);
            z = floorf(z / 2.0f + 0.2f) * 2.0f;

            (*objects)[i * rowCol + j].position = (vec3){i * 2.0f + x , j * 2.0f + y, z - 25.0f};
            (*objects)[i * rowCol + j].scale = (vec3){0.3f, 0.3f, 0.3f};
            (*objects)[i * rowCol + j].rotation = (vec3){0.0f, 0.0f, 0.0f};
        }
    }
}

void createGameObjects(GameObject** objects, uint32_t chunks, long seed, const char* regionDirectory) {
    uint32_t chunkSize = 16 * 16;
    uint32_t totalObjects = chunkSize * chunks * chunks;

    *objects = (GameObject*)malloc(totalObjects * sizeof(GameObject));

    if (!(*objects)) {
        printf("Memory allocation failed!\n");
        return;
    }

    for (uint32_t i = 0; i < chunks; i++) {
        for(uint32_t j = 0; j < chunks; j++){
            GameObject* chunkObjects;
            float x = i * 16 * 2.0f;
            float y = j * 16 * 2.0f;
    
            createChunk(&chunkObjects, 16, seed, x, y, i, j);
    
            memcpy(*objects + (i * chunks + j) * chunkSize, chunkObjects, chunkSize * sizeof(GameObject));

            vec2 regionPosition = { x, y };
            writeVFCRegion(regionDirectory, *objects + (i * chunks + j) * chunkSize, chunkSize, regionPosition);
    
            free(chunkObjects);
        }
    }
}

void loadGameObjects(GameObject** objects, uint32_t chunks, long seed, const char* regionDirectory) {
    char vfmFileName[40];
    sprintf(vfmFileName, "%s/.vfm", regionDirectory);
    uint32_t regionCount;
    
    FILE *vfmFile;

    char** regions = loadVFMFile(vfmFileName, &regionCount);

    if(fopen_s(&vfmFile, vfmFileName, "r") != 0){
        fprintf(stderr, "failed to open vfm file!");
    }

    uint32_t lineCount = 0;
    char buffer[32];

    while (fgets(buffer, sizeof(buffer), vfmFile)) {
        lineCount++;
    }

    fclose(vfmFile);

    *objects = NULL;
    uint32_t totalObjects = 0;

    VFCHeader header;

    for(uint32_t i = 0; i < lineCount; i++){
        uint32_t gameObjectCount;
        vec2 xy;

        if(sscanf_s(regions[i], "r-%f-%f", &xy.x, &xy.y) == 2){
            GameObject* newObjects = NULL;

            loadVFCRegion(regionDirectory, xy, &newObjects, &gameObjectCount, &header);

            if (gameObjectCount > 0) {
                *objects = realloc(*objects, (totalObjects + gameObjectCount) * sizeof(GameObject));
                if (!(*objects)) {
                    fprintf(stderr, "Memory allocation failed!\n");
                    return;
            }

            memcpy(*objects + totalObjects, newObjects, gameObjectCount * sizeof(GameObject));
            totalObjects += gameObjectCount;

            free(newObjects);
        }
    }
}
}