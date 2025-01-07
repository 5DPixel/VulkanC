#pragma once

#include <vulkan/vulkan.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../constants_and_arrays/constants_and_arrays.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physicalDevice, VkSurfaceKHR* surface);
bool isDeviceSuitable(VkPhysicalDevice* device, VkSurfaceKHR* surface);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice* device, VkSurfaceKHR* surface);
void createSurface(VkInstance instance, GLFWwindow* window, VkSurfaceKHR* surface);
bool checkDeviceExtensionSupport(VkPhysicalDevice* device);
void createLogicalDevice(VkDevice* device, VkPhysicalDevice* physicalDevice, VkQueue* graphicsQueue, VkQueue* presentQueue, VkSurfaceKHR* surface);