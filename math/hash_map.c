#include "hash_map.h"

vertexHashMapItem* binarySearch(vertexHashMapItem* items, uint32_t size, const Vertex key){
    if(size + size < size){
        return NULL;
    }
    uint32_t low = 0;
    uint32_t high = size;

    while(low < high){
        uint32_t mid = (low + high) / 2;
        int c = assertVertexStructsEqual(items[mid].key, key);
        if (c == 0) {
            return &items[mid];
        }
        if (c < 0) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return NULL;
}

vertexHashMapItem* deduplicateVertices(vertexHashMapItem* items, uint32_t size){
    if(size + size < size){
        return NULL;
    }

    printf("%f", items[0].key.pos.x);
    return NULL;
}

vertexHashMapItem* createVertexHashMap(Vertex* vertices, uint32_t size){
    vertexHashMapItem* items = malloc(size * sizeof(vertexHashMapItem));

    for(uint32_t i = 0; i < size; i++){
        items[i].key = vertices[i];
        items[i].value = i;
    }

    return items;
}