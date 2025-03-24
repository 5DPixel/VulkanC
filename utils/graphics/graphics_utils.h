#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include "../buffer/buffer_utils.h"
#include "../../file/file_utils.h"
#include "../swapchain/swapchain_utils.h"
#include "../../obj/obj_loader.h"

VkShaderModule createShaderModule(char* source, size_t codeSize, VkDevice* device);
void createRenderPass(VkFormat swapChainImageFormat, VkRenderPass* renderPass, VkDevice device, VkPhysicalDevice physicalDevice);
void createGraphicsPipeline(VkDevice* device, VkExtent2D swapChainExtent, VkPipelineLayout* pipelineLayout, VkRenderPass renderPass, VkPipeline* graphicsPipeline, VkShaderModule* vertShaderModule, VkShaderModule* fragShaderModule, VkDescriptorSetLayout descriptorSetLayout);
void drawFrame(VkDevice device, VkFence* inFlightFences, VkSemaphore* imageAvailableSemaphores, VkSwapchainKHR swapChain, VkCommandBuffer* commandBuffers, VkRenderPass renderPass, VkFramebuffer* swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline, VkSemaphore* renderFinishedSemaphores, VkQueue graphicsQueue, VkQueue presentQueue, uint32_t currentFrame, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window, VkImage* swapChainImages, VkFormat swapChainImageFormat, uint32_t imageCount, VkImageView* swapChainImageViews, VkBuffer vertexBuffer, VkBuffer indexBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet* descriptorSets, void** uniformBuffersMapped, VkImageView depthImageView, uint32_t indexCount, Camera* camera, GameObject* gameObjects, uint32_t gameObjectCount, void **shaderStorageBuffersMapped, vec3 clearColor);
void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage* image, VkDeviceMemory* imageMemory, VkDevice device, VkPhysicalDevice physicalDevice, uint32_t mipLevels);
void createTextureImage(VkDevice device, VkPhysicalDevice physicalDevice, VkImage* textureImage, VkDeviceMemory* textureImageMemory, VkCommandPool commandPool, VkQueue graphicsQueue, uint32_t* mipLevels, VkFormat imageFormat);
void createTextureImageView(VkImage textureImage, VkImageView* textureImageView, VkDevice device, uint32_t mipLevels);
void createTextureSampler(VkPhysicalDevice physicalDevice, VkSampler* sampler, VkDevice device, uint32_t mipLevels);
VkFormat findSupportedFormat(VkFormat* candidates, uint32_t candidateAmount, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice physicalDevice);
VkFormat findDepthFormat(VkPhysicalDevice physicalDevice);
bool hasStencilComponent(VkFormat format);
VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkDevice device);
void createDepthResources(VkImage* depthImage, VkDeviceMemory* depthImageMemory, VkImageView* depthImageView, VkPhysicalDevice physicalDevice, VkExtent2D swapChainExtent, VkDevice device, VkImageView** swapChainImageViews, VkCommandPool commandPool, VkQueue graphicsQueue);
void generateMipmaps(VkImage image, int32_t texWidth, int32_t texHeight, uint32_t mipLevels, VkCommandPool commandPool, VkDevice device, VkQueue graphicsQueue, VkPhysicalDevice physicalDevice, VkFormat imageFormat);
void loadModel(Vertex** vertices, uint32_t* vertexCount, uint32_t** indices, uint32_t* indexCount);