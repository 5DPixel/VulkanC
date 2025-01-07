#pragma once

#include <vulkan/vulkan.h>
#include "../../math/math_utils.h"

#define INVALID_FAMILY_INDEX -1
#define MAX_FRAMES_IN_FLIGHT 2

//STRUCT
typedef struct QueueFamilyIndices {
    uint32_t graphicsFamily;
    uint32_t presentFamily;
} QueueFamilyIndices;

typedef struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    VkSurfaceFormatKHR* formats;
    VkPresentModeKHR* presentModes;
    uint32_t formatCount;
    uint32_t presentModeCount;
} SwapChainSupportDetails;

typedef struct {
    mat4 model;
    mat4 view;
    mat4 projection;
} UniformBufferObject;

typedef struct {
    vec2 pos;
    vec3 color;
} Vertex;

extern const char* validationLayers[1];
extern const char* deviceExtensions[1];