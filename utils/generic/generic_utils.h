#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../math/math_utils.h"
#include "../../file/file_utils.h"
#include "../window/window_utils.h"
#include "../constants_and_arrays/constants_and_arrays.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

//FUNCTIONS
void createInstance(VkInstance* instance);
void cleanup(GLFWwindow* window, VkDevice device, VkPhysicalDevice physicalDevice, VkInstance instance, VkSurfaceKHR surface, VkSwapchainKHR swapChain, VkImageView* swapChainImageViews, uint32_t swapChainImageViewCount, VkShaderModule vertShaderModule, VkShaderModule fragShaderModule, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, VkPipeline graphicsPipeline, VkFramebuffer* swapChainFrameBuffers, VkCommandPool commandPool, VkSemaphore* imageAvailableSemaphores, VkSemaphore* renderFinishedSemaphores, VkFence* inFlightFences, VkBuffer vertexBuffer, VkDeviceMemory vertexBufferMemory, VkBuffer indexBuffer, VkDeviceMemory indexBufferMemory, VkDescriptorSetLayout descriptorSetLayout, VkBuffer* uniformBuffers, VkDeviceMemory* uniformBuffersMemory, VkDescriptorPool descriptorPool);
void createSyncObjects(VkDevice device, VkSemaphore** imageAvailableSemaphores, VkSemaphore** renderFinishedSemaphores, VkFence** inFlightFences);