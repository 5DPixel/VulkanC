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

int compareVertices(const void* a, const void* b) {
    vertexHashMapItem* itemA = (vertexHashMapItem*)a;
    vertexHashMapItem* itemB = (vertexHashMapItem*)b;
    return assertVertexStructsEqual(itemA->key, itemB->key);
}

vertexHashMapItem* deduplicateVertices(vertexHashMapItem* items, uint32_t size, uint32_t* newSize) {
    if (size == 0) {
        *newSize = 0;
        return NULL;
    }

    qsort(items, size, sizeof(vertexHashMapItem), compareVertices);

    uint32_t uniqueCount = 1;
    for (uint32_t i = 1; i < size; i++) {
        if (assertVertexStructsEqual(items[i].key, items[i - 1].key) != 0) {
            items[uniqueCount] = items[i];
            uniqueCount++;
        }
    }

    for (uint32_t i = 0; i < uniqueCount; i++) {
        items[i].value = i;
    }

    vertexHashMapItem* uniqueItems = realloc(items, uniqueCount * sizeof(vertexHashMapItem));
    if (!uniqueItems) {
        free(items);
        return NULL;
    }

    *newSize = uniqueCount;
    return uniqueItems;
}
vertexHashMapItem* createVertexHashMap(Vertex* vertices, uint32_t size){
    vertexHashMapItem* items = malloc(size * sizeof(vertexHashMapItem));

    for(uint32_t i = 0; i < size; i++){
        items[i].key = vertices[i];
        items[i].value = i;
    }

    return items;
}