#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../utils/constants_and_arrays/constants_and_arrays.h"

#define CURRENT_HDB_VERSION MAKE_VERSION(1, 0, 0)
#define CURRENT_HDB_VERSION_STRING "1.0.0"

typedef enum {
    NONE = 0,
    ZLIB = 1,
    GZIP = 2, //Not supported yet
    DEFLATE = 3 //Not supported yet
} CompressionType;

typedef struct {
    char hdbMagicByte[4];
    uint16_t hdbVersion;
    uint16_t hdbFlags;
    uint32_t hdbUncompressedSize;
    uint32_t hdbCompressedSize;
    uint32_t hdbChecksum;
    CompressionType hdbCompressionType;
} HexDBHeader;

typedef enum {
    TYPE_UINT32,
    TYPE_STRING,
    TYPE_FLOAT
} ValueType;

typedef struct {
    char key[50];
    ValueType type;
    union {
        uint32_t uValue;
        float fValue;
        char strValue[100];
    } value;
} KeyValuePair;

void writeHexDBDatabase(const char* fileName, KeyValuePair* keyValues, uint32_t keyValuePairCount);
void loadHexDBDatabase(const char* fileName, KeyValuePair** keyValuePairs, uint32_t keyValuePairCount);