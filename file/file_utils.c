#include "file_utils.h"
#include <stdlib.h>

char* readFile(const char* fileName, size_t* outSize){
    FILE *file;
    
    errno_t error_code;

    error_code = fopen_s(&file, fileName, "rb");
    if(error_code != 0){
        fprintf(stderr, "failed to open file!");
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)malloc(fileSize * sizeof(char));
    if(buffer == NULL){
        fprintf(stderr, "memory allocation for file buffer failed!\n");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading the full file content!\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    fclose(file);

    if (outSize) {
        *outSize = (size_t)fileSize;
    }

    return buffer;

    free(buffer);
}