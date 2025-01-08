#include "image_parser.h"

void printFileHeader(BMPFileHeader fileHeader) {
   printf("\nType: %c%c\n", fileHeader.bfType[0],fileHeader.bfType[1]);
   printf("Size: %d\n", fileHeader.bfSize);
   printf("Offset: %d\n", fileHeader.bfOffBits);
}

void printImageHeader(BMPImageHeader imageHeader) {
   printf("\nSize of header: %d\n", imageHeader.biSize);
   printf("Width: %d\n", imageHeader.biWidth);
   printf("Height: %d\n", imageHeader.biHeight);
   printf("Color Planes: %d\n", imageHeader.biPlanes);
   printf("Bits per Pixel: %d\n", imageHeader.biBitCount);
   printf("Compression: %d\n", imageHeader.biCompression);
   printf("Image size: %d\n", imageHeader.biSizeImage);
   printf("Preferred resolution in pixels per meter (X-Y): %d-%d\n", imageHeader.biXPelsPerMeter, imageHeader.biYPelsPerMeter);
   printf("Number color map: %d\n", imageHeader.biClrUsed);
   printf("Number of significant colors: %d\n", imageHeader.biClrImportant);
}

unsigned char* readV3Bitmap(const char* filePath, int* outWidth, int* outHeight){
    FILE* image;
    BMPFileHeader header;
    BMPImageHeader imageHeader;
    errno_t error_code;

    error_code = fopen_s(&image, filePath, "rb");
    if(error_code != 0){
        fprintf(stderr, "failed to open file!");
    }

    fseek(image, 0, SEEK_END);
    long fileSize = ftell(image);
    fseek(image, 0, SEEK_SET);

    fread(&header, sizeof(BMPFileHeader), 1, image);

    printf("File header information:");
    printFileHeader(header);

    if(header.bfType[0] != 'B' || header.bfType[1] != 'M') {
        fprintf(stderr, "file is not valid BMP image!");
        fclose(image);
        return;
    }

    fread(&imageHeader, sizeof(BMPImageHeader), 1, image);

    printf("\nImage header information:");
    printImageHeader(imageHeader);

    if(imageHeader.biSize != 40 || imageHeader.biCompression != 0) {
        fprintf(stderr, "file is not valid BMP image!");
        fclose(image);
        return;
    }

    int colorPaletteSize = imageHeader.biClrUsed * sizeof(RGBQuad);
    RGBQuad* colorPalette = (RGBQuad*)malloc(colorPaletteSize);
    if (colorPalette == NULL) {
        fprintf(stderr, "failed to allocate memory for color palette!\n");
        fclose(image);
        return;
    }

    fread(colorPalette, sizeof(RGBQuad), imageHeader.biClrUsed, image);
    fseek(image, header.bfOffBits, SEEK_SET);

    int width = imageHeader.biWidth;
    int height = imageHeader.biHeight;
    int rowSize = (width + 1) / 2;
    unsigned char* pixelData = (unsigned char*)malloc(imageHeader.biSizeImage);
    if (pixelData == NULL) {
        fprintf(stderr, "Failed to allocate memory for pixel data!\n");
        free(colorPalette);
        fclose(image);
        return;
    }

    fread(pixelData, 1, imageHeader.biSizeImage, image);

    unsigned char* pixels = (unsigned char*)malloc(width * height * sizeof(unsigned char));
    if (pixels == NULL) {
        fprintf(stderr, "failed to allocate memory for the final pixel array!\n");
        free(pixelData);
        free(colorPalette);
        fclose(image);
        return NULL;
    }

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            int byteIndex = y * rowSize + x / 2;
            int bitIndex = (x % 2) * 4;
            unsigned char pixelByte = pixelData[byteIndex];
            unsigned char pixelValue = (pixelByte >> (4 * (x % 2))) & 0x0F;

            pixels[y * width + x] = pixelValue;
        }
    }

    free(pixelData);
    free(colorPalette);
    fclose(image);

    *outWidth = width;
    *outHeight = height;

    return pixels;
}