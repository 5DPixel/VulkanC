#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include <time.h>
#include "../device_and_surface/device_utils.h"
#include "../constants_and_arrays/constants_and_arrays.h"
#include "../graphics/graphics_utils.h"

void createCommandPools(VkPhysicalDevice* physicalDevice, VkCommandPool* commandPool, VkSurfaceKHR* surface, VkDevice device);
void createCommandBuffers(VkCommandBuffer** commandBuffers, VkDevice device, VkCommandPool commandPool);
void createVertexBuffer(Vertex* vertices, uint32_t vertexCount, VkBuffer* vertexBuffer, VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceMemory* vertexBufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue);
void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory, VkDevice device, VkPhysicalDevice physicalDevice);
void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandPool commandPool, VkDevice device, VkQueue graphicsQueue);
void createIndexBuffer(uint32_t* indices, uint32_t indexCount, VkBuffer* indexBuffer, VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceMemory* indexBufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue);
VkVertexInputBindingDescription getBindingDescription();
VkVertexInputAttributeDescription* getAttributeDescriptions();
uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);
void createDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout* descriptorSetLayout);
void createUniformBuffers(VkBuffer** uniformBuffers, VkDeviceMemory** uniformBuffersMemory, void*** uniformBuffersMapped, VkDevice device, VkPhysicalDevice physicalDevice);
void createShaderStorageBuffers(VkBuffer** shaderStorageBuffers, VkDeviceMemory** shaderStorageBuffersMemory, void*** shaderStorageBuffersMapped, VkDevice device, VkPhysicalDevice physicalDevice);
void updateUniformBuffer(uint32_t currentImage, VkExtent2D swapChainExtent, void** uniformBuffersMapped, Camera* camera, GameObject* gameObjects, uint32_t gameObjectCount);
void updateShaderStorageBuffers(uint32_t currentImage, VkExtent2D swapChainExtent, void** shaderStorageBuffersMapped, GameObject* gameObjects, uint32_t gameObjectCount);
void createDescriptorPool(VkDevice device, VkDescriptorPool* descriptorPool);
void createDescriptorSets(VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool descriptorPool, VkDescriptorSet** descriptorSets, VkDevice device, VkBuffer* uniformBuffers, VkSampler textureSampler, VkImageView textureImageView, VkBuffer* shaderStorageBuffers);
VkCommandBuffer beginSingleTimeCommands(VkCommandPool commandPool, VkDevice device);
void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue graphicsQueue, VkCommandPool commandPool, VkDevice device);
void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool commandPool, VkDevice device, VkQueue graphicsQueue, uint32_t mipLevels);
void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, VkCommandPool commandPool, VkDevice device, VkQueue graphicsQueue);
void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, VkRenderPass renderPass, VkFramebuffer* swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline, VkBuffer vertexBuffer, VkBuffer indexBuffer, VkPipelineLayout pipelineLayout, VkDescriptorSet* descriptorSets, uint32_t currentFrame, uint32_t indexCount, GameObject** gameObjects, uint32_t gameObjectCount, vec3 skyClearColor);