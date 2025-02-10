#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef _WIN32
    #include <direct.h>
    #define create_folder(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define create_folder(path) mkdir(path, 0777)
#endif

uint8_t* generateRandomBytes(uint32_t length);
char* base64Encode(const uint8_t* input, uint32_t inputLength);