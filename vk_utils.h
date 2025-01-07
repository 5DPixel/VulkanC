#ifndef VK_UTILS_H
#define VK_UTILS_H

#include <vulkan/vulkan.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "math/math_utils.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define INVALID_FAMILY_INDEX -1
#define MAX_FRAMES_IN_FLIGHT 2

//STRUCTS
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
    vec2 pos;
    vec3 color;
} Vertex;

//FUNCTIONS
void initWindow(GLFWwindow** window, int width, int height, char* windowName);
void printExtensions();
bool checkValidationLayerSupport();
void createInstance(VkInstance* instance);
const char** getRequiredExtensions(uint32_t* count);
bool isDeviceSuitable(VkPhysicalDevice* device, VkSurfaceKHR* surface);
void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physicalDevice, VkSurfaceKHR* surface);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice* device, VkSurfaceKHR* surface);
void createLogicalDevice(VkDevice* device, VkPhysicalDevice* physicalDevice, VkQueue* graphicsQueue, VkQueue* presentQueue, VkSurfaceKHR* surface);
void cleanup(GLFWwindow* window, VkDevice device, VkPhysicalDevice physicalDevice, VkInstance instance, VkSurfaceKHR surface, VkSwapchainKHR swapChain, VkImageView* swapChainImageViews, uint32_t swapChainImageViewCount, VkShaderModule vertShaderModule, VkShaderModule fragShaderModule, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, VkPipeline graphicsPipeline, VkFramebuffer* swapChainFrameBuffers, VkCommandPool commandPool, VkSemaphore* imageAvailableSemaphores, VkSemaphore* renderFinishedSemaphores, VkFence* inFlightFences, VkBuffer vertexBuffer, VkDeviceMemory vertexBufferMemory, VkBuffer indexBuffer, VkDeviceMemory indexBufferMemory);
void createSurface(VkInstance instance, GLFWwindow* window, VkSurfaceKHR* surface);
bool checkDeviceExtensionSupport(VkPhysicalDevice* device);
SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice* device, VkSurfaceKHR* surface);
VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR* availableFormats, uint32_t formatCount);
VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR* availablePresentModes, uint32_t presentModeCount);
VkExtent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR capabilities, GLFWwindow* window);
void createSwapChain(VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface, GLFWwindow* window, VkSwapchainKHR* swapChain, VkDevice* device, VkImage** swapChainImages, VkFormat* swapChainImageFormat, VkExtent2D* swapChainExtent, uint32_t* imageCount);
void createImageViews(VkImageView** swapChainImageViews, VkImage* swapChainImages, VkFormat* swapChainImageFormat, uint32_t* imageCount, VkDevice* device);
VkShaderModule createShaderModule(char* source, size_t codeSize, VkDevice* device);
void createGraphicsPipeline(VkDevice* device, VkExtent2D swapChainExtent, VkPipelineLayout* pipelineLayout, VkRenderPass renderPass, VkPipeline* graphicsPipeline, VkShaderModule* vertShaderModule, VkShaderModule* fragShaderModule);
void createRenderPass(VkFormat swapChainImageFormat, VkRenderPass* renderPass, VkDevice device);
void createFramebuffers(VkFramebuffer** swapChainFrameBuffers, VkImageView* swapChainImageViews, uint32_t imageCount, VkRenderPass renderPass, VkExtent2D swapChainExtent, VkDevice device);
void createCommandPools(VkPhysicalDevice* physicalDevice, VkCommandPool* commandPool, VkSurfaceKHR* surface, VkDevice device);
void createCommandBuffers(VkCommandBuffer** commandBuffers, VkDevice device, VkCommandPool commandPool);
void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, VkRenderPass renderPass, VkFramebuffer* swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline, VkBuffer vertexBuffer, VkBuffer indexBuffer);
void drawFrame(VkDevice device, VkFence* inFlightFences, VkSemaphore* imageAvailableSemaphores, VkSwapchainKHR swapChain, VkCommandBuffer* commandBuffers, VkRenderPass renderPass, VkFramebuffer* swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline, VkSemaphore* renderFinishedSemaphores, VkQueue graphicsQueue, VkQueue presentQueue, uint32_t currentFrame, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window, VkImage* swapChainImages, VkFormat swapChainImageFormat, uint32_t imageCount, VkImageView* swapChainImageViews, VkBuffer vertexBuffer, VkBuffer indexBuffer);
void createSyncObjects(VkDevice device, VkSemaphore** imageAvailableSemaphores, VkSemaphore** renderFinishedSemaphores, VkFence** inFlightFences);
void recreateSwapChain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window, VkSwapchainKHR swapChain, VkImage* swapChainImages, VkFormat swapChainImageFormat, VkExtent2D swapChainExtent, uint32_t imageCount, VkImageView* swapChainImageViews, VkFramebuffer* swapChainFramebuffers, VkRenderPass renderPass);
VkVertexInputBindingDescription getBindingDescription();
VkVertexInputAttributeDescription* getAttributeDescriptions();
void createVertexBuffer(Vertex* vertices, uint32_t vertexCount, VkBuffer* vertexBuffer, VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceMemory* vertexBufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue);
uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);
void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory, VkDevice device, VkPhysicalDevice physicalDevice);
void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandPool commandPool, VkDevice device, VkQueue graphicsQueue);
void createIndexBuffer(uint16_t* indices, uint32_t indexCount, VkBuffer* indexBuffer, VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceMemory* indexBufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue);

#endif