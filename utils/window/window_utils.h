#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "../constants_and_arrays/constants_and_arrays.h"

void initWindow(GLFWwindow** window, int width, int height, char* windowName);
void printExtensions();
bool checkValidationLayerSupport();
const char** getRequiredExtensions(uint32_t* count);