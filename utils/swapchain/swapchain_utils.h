#pragma once

#include <vulkan/vulkan.h>
#include <stdio.h>
#include "../constants_and_arrays/constants_and_arrays.h"
#include "../device_and_surface/device_utils.h"

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice* device, VkSurfaceKHR* surface);
VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR* availableFormats, uint32_t formatCount);
VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR* availablePresentModes, uint32_t presentModeCount);
VkExtent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR capabilities, GLFWwindow* window);
void createSwapChain(VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface, GLFWwindow* window, VkSwapchainKHR* swapChain, VkDevice* device, VkImage** swapChainImages, VkFormat* swapChainImageFormat, VkExtent2D* swapChainExtent, uint32_t* imageCount);
void createImageViews(VkImageView** swapChainImageViews, VkImage* swapChainImages, VkFormat* swapChainImageFormat, uint32_t* imageCount, VkDevice* device);
void createFramebuffers(VkFramebuffer** swapChainFrameBuffers, VkImageView* swapChainImageViews, uint32_t imageCount, VkRenderPass renderPass, VkExtent2D swapChainExtent, VkDevice device);
void recreateSwapChain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window, VkSwapchainKHR swapChain, VkImage* swapChainImages, VkFormat swapChainImageFormat, VkExtent2D swapChainExtent, uint32_t imageCount, VkImageView* swapChainImageViews, VkFramebuffer* swapChainFramebuffers, VkRenderPass renderPass);