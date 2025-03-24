#include "game_logic.h"

Keyframe keyframes[] = {
    {0, {255, 150, 100}},
    {6000, {135, 206, 235}},
    {12000, {255, 102, 102}},
    {18000, {10, 10, 50}},
    {24000, {255, 150, 100}}
};

#define NUM_KEYFRAMES (sizeof(keyframes) / sizeof(keyframes[0]))

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

    writeVFMFile(regionDirectory);
}

void loadGameObjects(GameObject** objects, uint32_t chunks, long seed, const char* regionDirectory) {
    char vfmFileName[150];
    char levelNameFileName[150];

    sprintf(levelNameFileName, "%s/db/levelname.txt", regionDirectory);
    sprintf(vfmFileName, "%s/regions/regions.vfm", regionDirectory);

    uint32_t regionCount;
    
    FILE *vfmFile;
    FILE *levelNameFile;

    char** regions = loadVFMFile(vfmFileName, &regionCount);

    if(fopen_s(&vfmFile, vfmFileName, "r") != 0){
        fprintf(stderr, "failed to open vfm file!");
    }

    if (fopen_s(&levelNameFile, levelNameFileName, "r") != 0) {
        printf("failed to open levelname file!\n");
    }

    char levelName[32];

    if (fgets(levelName, sizeof(levelName), levelNameFile) != NULL) {
        printf("Opened World: %s\n", levelName);
    } else {
        printf("error reading file or file is empty\n");
    }

    fclose(levelNameFile);

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

vec3 getSkyColor(int tick){
    tick = tick % 24000;

    for(uint32_t i = 0; i < NUM_KEYFRAMES - 1; i++){
        if(tick >= keyframes[i].time && tick < keyframes[i + 1].time){
            float ratio = (float)(tick - keyframes[i].time) / (keyframes[i + 1].time - keyframes[i].time);
            vec3 result = vec3Lerp(keyframes[i].value, keyframes[i + 1].value, ratio);
            result = (vec3){result.x / 255.0f, result.y / 255.0f, result.z / 255.0f};
            
            return result;
        }
    }
    return keyframes[0].value;
}