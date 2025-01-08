#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../file/file_utils.h"

#pragma pack(push, 1)
typedef struct {
    char bfType[2];
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMPFileHeader;

typedef struct {
    uint32_t biSize;
    int biWidth;
    int biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPImageHeader;

typedef struct {
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
} RGBQuad;

#pragma pack(pop)

void printFileHeader(BMPFileHeader fileHeader);
void printImageHeader(BMPImageHeader imageHeader);
unsigned char* readV3Bitmap(const char* filePath, int* outWidth, int* outHeight);