#include "encode.h"

static const char base64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

uint8_t* generateRandomBytes(uint32_t length){
    uint8_t* buffer = (uint8_t*)malloc(length);
    if (!buffer) {
        return NULL;
    }

    for(uint32_t i = 0; i < length; i++){
        buffer[i] = rand() % 256;
    }

    return buffer;
}

char* base64Encode(const uint8_t* input, uint32_t inputLength){
    uint32_t outputLength = ((inputLength + 2) / 3) * 4;
    char* output = (char*)malloc(outputLength + 1);
    if (!output) {
        return NULL;
    }

    uint32_t i, j;
    for(i = 0, j = 0; i < inputLength;){
        uint32_t octetA = i < inputLength ? input[i++] : 0;
        uint32_t octetB = i < inputLength ? input[i++] : 0;
        uint32_t octetC = i < inputLength ? input[i++] : 0;

        uint32_t triple = (octetA << 16) | (octetB << 8) | octetC;

        output[j++] = base64Chars[(triple >> 18) & 0x3F];
        output[j++] = base64Chars[(triple >> 12) & 0x3F];
        output[j++] = (i > inputLength + 1) ? '=' : base64Chars[(triple >> 6) & 0x3F];
        output[j++] = (i > inputLength) ? '=' : base64Chars[triple & 0x3F];
    }
    output[j] = '\0';
    return output;
}