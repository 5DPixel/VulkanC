#include "hexdb_loader.h"

#include "../zlib/miniz.h"

void writeHexDBDatabase(const char* fileName, KeyValuePair* keyValues, uint32_t keyValuePairCount){
    FILE *file;

    if(fopen_s(&file, fileName, "wb") != 0){
        fprintf(stderr, "failed to open hexdb file!\n");
    }

    uint32_t uncompressedSize = sizeof(KeyValuePair) * keyValuePairCount;
    uint32_t compressedSize = mz_compressBound(uncompressedSize);
    void* compressedData = malloc(compressedSize);

    if(!compressedData){
        fprintf(stderr, "failed to allocate memory for compression!\n");
        fclose(file);
        
        return;
    }

    int result = mz_compress((unsigned char*)compressedData, &compressedSize, (unsigned char*)keyValues, uncompressedSize);

    if(result != MZ_OK){
        fprintf(stderr, "compression failed!\n");
        free(compressedData);
        fclose(file);
        return;
    }

    HexDBHeader header = {
        .hdbMagicByte = "HDB\x00",
        .hdbVersion = CURRENT_HDB_VERSION,
        .hdbFlags = 0,
        .hdbUncompressedSize = uncompressedSize,
        .hdbCompressedSize = compressedSize,
        .hdbChecksum = 0,
        .hdbCompressionType = ZLIB
    };

    fwrite(&header, sizeof(header), 1, file);
    fwrite(compressedData, 1, compressedSize, file);
    fclose(file);
}

void loadHexDBDatabase(const char* fileName, KeyValuePair** keyValuePairs, uint32_t keyValuePairCount){
    FILE *file;

    if(fopen_s(&file, fileName, "rb") != 0){
        fprintf(stderr, "failed to open hexDB file!\n");
        return;
    }

    HexDBHeader header;
    fread(&header, sizeof(HexDBHeader), 1, file);

    if(header.hdbMagicByte[0] != 'H' || header.hdbMagicByte[1] != 'D' || header.hdbMagicByte[2] != 'B' || header.hdbMagicByte[3] != '\0'){
        fprintf(stderr, "invalid hexDB file: magic byte mismatch\n");
        fclose(file);
        return;
    }

    if(header.hdbCompressionType != ZLIB){
        return;
    }

    void* compressedData = malloc(header.hdbCompressedSize);
    if(!compressedData){
        fprintf(stderr, "failed to allocate memory for compressed data!\n");
        fclose(file);
        return;
    }

    fread(compressedData, 1, header.hdbCompressedSize, file);
    fclose(file);

    *keyValuePairs = (KeyValuePair*)malloc(header.hdbUncompressedSize);
    if(!*keyValuePairs){
        fprintf(stderr, "failed to allocate memory for decompression!\n");
        free(compressedData);
        return;
    }

    uint32_t uncompressedSize = header.hdbUncompressedSize;
    int result = mz_uncompress((unsigned char*)*keyValuePairs, &uncompressedSize, 
                               (unsigned char*)compressedData, header.hdbCompressedSize);

    free(compressedData);

    if (result != MZ_OK || uncompressedSize != header.hdbUncompressedSize) {
        fprintf(stderr, "decompression failed!\n");
        free(*keyValuePairs);
        *keyValuePairs = NULL;
        return;
    }

    fclose(file);
}