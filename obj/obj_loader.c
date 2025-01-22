#include "obj_loader.h"

void loadOBJ(const char* filePath, Vertex** vertices, uint32_t* vertexCount, uint32_t** indices, uint32_t* indexCount) {
    FILE* file;
    errno_t errorCode;
    
    errorCode = fopen_s(&file, filePath, "r");
    if (errorCode != 0) {
        fprintf(stderr, "Failed to open OBJ file: %s\n", filePath);
        return;
    }

    vec3* positions = NULL;
    vec2* texCoords = NULL; 
    vec3* normals = NULL;
    uint32_t posCount = 0, texCount = 0, normalCount = 0;

    vertexHashMapItem* vertexMap;

    char line[128];
    *vertexCount = 0;
    *indexCount = 0;
    *vertices = NULL;
    *indices = NULL;

    while(fgets(line, sizeof(line), file)){
        if(isspace(line[0])){
            continue;
        }
        
        if (line[0] == 'v' && line[1] == ' '){
            vec3 pos;
            if (sscanf_s(line, "v %f %f %f", &pos.x, &pos.y, &pos.z) == 3) {
                posCount++;
                positions = realloc(positions, posCount * sizeof(vec3));
                positions[posCount - 1] = pos;
            }
        }

        if(line[0] == 'v' && line[1] == 't'){
            vec2 tex;
            if (sscanf_s(line, "vt %f %f", &tex.x, &tex.y) == 2) {
                texCount++;

                tex.y = 1.0f - tex.y;
                texCoords = realloc(texCoords, texCount * sizeof(vec2));
                texCoords[texCount - 1] = tex;
            }
        }

        if(line[0] == 'v' && line[1] == 'n'){
            vec3 normal;
            if (sscanf_s(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z) == 3) {
                normalCount++;
                normals = realloc(normals, normalCount * sizeof(vec3));
                normals[normalCount - 1] = normal;
            }
        }

        if(line[0] == 'f' && line[1] == ' '){
            uint32_t posIndex[3], texIndex[3], normalIndex[3];
            int matches = sscanf_s(line, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &posIndex[0], &texIndex[0], &normalIndex[0], &posIndex[1], &texIndex[1], &normalIndex[1], &posIndex[2], &texIndex[2], &normalIndex[2]);

            if(matches != 9){
                fprintf(stderr, "failed to parse face data!");
            }

            for(int i = 0; i < 3; i++){
                uint32_t pIdx = posIndex[i] - 1;
                uint32_t tIdx = texIndex[i] - 1;
                uint32_t nIdx = normalIndex[i] - 1;

                Vertex vertex = {
                    .pos = positions[pIdx],
                    .texCoord = texCoords[tIdx],
                    .color = {1.0f, 1.0f, 1.0f},
                    .normal = normals[nIdx]
                };
                (*vertexCount)++;
                *vertices = realloc(*vertices, (*vertexCount) * sizeof(Vertex));
                (*vertices)[*vertexCount - 1] = vertex;

                (*indexCount)++;
                *indices = realloc(*indices, (*indexCount) * sizeof(uint32_t));
                (*indices)[*indexCount - 1] = *vertexCount - 1;
            }
        }
    }

    vertexMap = createVertexHashMap(*vertices, *vertexCount);
    deduplicateVertices(vertexMap, *vertexCount);

    free(positions);
    free(texCoords);
    fclose(file);
}