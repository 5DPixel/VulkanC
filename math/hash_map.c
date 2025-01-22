#include "hash_map.h"

vertexHashMapItem* linearSearch(vertexHashMapItem* items, size_t size, const Vertex key){
    for(size_t i = 0; i < size; i++){
        if(assertVertexStructsEqual){
            return &items[i];
        }
    }

    return NULL;
}