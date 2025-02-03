#pragma once

#include <vulkan/vulkan.h>
#include <stdbool.h>
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
    vec3 pos;
    vec3 color;
    vec3 normal;
    vec2 texCoord;
} Vertex;

typedef struct {
    vec3 eye;
    vec3 center;
    vec3 up;

    vec3 right;
    vec3 rotation;

    float speed;
    float sensitivity;

    float fov;
    float nearClippingPlane;
    float farClippingPlane;
} Camera;

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;
} GameObject;

extern const char* validationLayers[1];
extern const char* deviceExtensions[1];

bool assertVertexStructsEqual(Vertex v1, Vertex v2);