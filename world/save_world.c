#include "save_world.h"

void createWorld(const char* worldDirectory, const char* levelName){
    uint8_t* bytes = generateRandomBytes(16);
    char* encoded = base64Encode(bytes, 16);
    char fileName[150];
    char resources[150];

    char levelNamePath[150];
    FILE* levelNameFile;

    char db[150];
    char regions[150];

    char playerData[150];

    sprintf(fileName, "%s/%s", worldDirectory, encoded);
    create_folder(fileName);

    sprintf(resources, "%s/%s/resources", worldDirectory, encoded);
    create_folder(resources);

    sprintf(db, "%s/%s/resources/db", worldDirectory, encoded);
    create_folder(db);

    sprintf(regions, "%s/%s/resources/regions", worldDirectory, encoded);
    create_folder(regions);

    sprintf(playerData, "%s/%s/resources/db/player", worldDirectory, encoded);
    create_folder(playerData);

    sprintf(levelNamePath, "%s/%s/resources/db/levelname.txt", worldDirectory, encoded);
    if(fopen_s(&levelNameFile, levelNamePath, "w") != 0){
        fprintf(stderr, "failed to open levelname file!\n");
    }

    fprintf(levelNameFile, "%s", levelName);
    fclose(levelNameFile);
}