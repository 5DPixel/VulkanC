#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include "../device_and_surface/device_utils.h"
#include "../constants_and_arrays/constants_and_arrays.h"

void createCommandPools(VkPhysicalDevice* physicalDevice, VkCommandPool* commandPool, VkSurfaceKHR* surface, VkDevice device);
void createCommandBuffers(VkCommandBuffer** commandBuffers, VkDevice device, VkCommandPool commandPool);
void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, VkRenderPass renderPass, VkFramebuffer* swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline, VkBuffer vertexBuffer, VkBuffer indexBuffer);
void createVertexBuffer(Vertex* vertices, uint32_t vertexCount, VkBuffer* vertexBuffer, VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceMemory* vertexBufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue);
void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* bufferMemory, VkDevice device, VkPhysicalDevice physicalDevice);
void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkCommandPool commandPool, VkDevice device, VkQueue graphicsQueue);
void createIndexBuffer(uint16_t* indices, uint32_t indexCount, VkBuffer* indexBuffer, VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceMemory* indexBufferMemory, VkCommandPool commandPool, VkQueue graphicsQueue);
VkVertexInputBindingDescription getBindingDescription();
VkVertexInputAttributeDescription* getAttributeDescriptions();
uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);