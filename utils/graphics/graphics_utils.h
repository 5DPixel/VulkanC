#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include "../buffer/buffer_utils.h"
#include "../../file/file_utils.h"
#include "../swapchain/swapchain_utils.h"

VkShaderModule createShaderModule(char* source, size_t codeSize, VkDevice* device);
void createRenderPass(VkFormat swapChainImageFormat, VkRenderPass* renderPass, VkDevice device);
void createGraphicsPipeline(VkDevice* device, VkExtent2D swapChainExtent, VkPipelineLayout* pipelineLayout, VkRenderPass renderPass, VkPipeline* graphicsPipeline, VkShaderModule* vertShaderModule, VkShaderModule* fragShaderModule, VkDescriptorSetLayout descriptorSetLayout);
void drawFrame(VkDevice device, VkFence* inFlightFences, VkSemaphore* imageAvailableSemaphores, VkSwapchainKHR swapChain, VkCommandBuffer* commandBuffers, VkRenderPass renderPass, VkFramebuffer* swapChainFramebuffers, VkExtent2D swapChainExtent, VkPipeline graphicsPipeline, VkSemaphore* renderFinishedSemaphores, VkQueue graphicsQueue, VkQueue presentQueue, uint32_t currentFrame, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window, VkImage* swapChainImages, VkFormat swapChainImageFormat, uint32_t imageCount, VkImageView* swapChainImageViews, VkBuffer vertexBuffer, VkBuffer indexBuffer);