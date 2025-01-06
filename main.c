#include <GLFW/glfw3.h>
#include <stdio.h>
#include "vk_utils.h"
#include "math/math_utils.h"
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#define WIDTH 800
#define HEIGHT 600
#define WINDOW_NAME "Vulkan Window"

int main(){
    //VARIABLES
    GLFWwindow *window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    VkImage* swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    VkImageView* swapChainImageViews;
    uint32_t imageCount;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    VkFramebuffer* swapChainFrameBuffers;
    VkCommandPool commandPool;
    VkCommandBuffer* commandBuffers;
    VkSemaphore* imageAvailableSemaphores;
    VkSemaphore* renderFinishedSemaphores;
    VkFence* inFlightFences;
    uint32_t currentFrame = 0;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    Vertex vertices[3] = {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 1.0f}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    initWindow(&window, WIDTH, HEIGHT, WINDOW_NAME);

    printExtensions();

    createInstance(&instance);
    createSurface(instance, window, &surface);
    pickPhysicalDevice(instance, &physicalDevice, &surface);
    createLogicalDevice(&device, &physicalDevice, &graphicsQueue, &presentQueue, &surface);
    createSwapChain(&physicalDevice, &surface, window, &swapChain, &device, &swapChainImages, &swapChainImageFormat, &swapChainExtent, &imageCount);
    createImageViews(&swapChainImageViews, swapChainImages, &swapChainImageFormat, &imageCount, &device);
    createRenderPass(swapChainImageFormat, &renderPass, device);
    createGraphicsPipeline(&device, swapChainExtent, &pipelineLayout, renderPass, &graphicsPipeline, &vertShaderModule, &fragShaderModule);
    createFramebuffers(&swapChainFrameBuffers, swapChainImageViews, imageCount, renderPass, swapChainExtent, device);
    createCommandPools(&physicalDevice, &commandPool, &surface, device);
    createVertexBuffer(vertices, &vertexBuffer, device, physicalDevice, &vertexBufferMemory);
    createCommandBuffers(&commandBuffers, device, commandPool);
    createSyncObjects(device, &imageAvailableSemaphores, &renderFinishedSemaphores, &inFlightFences);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame(device, inFlightFences, imageAvailableSemaphores, swapChain, commandBuffers, renderPass, swapChainFrameBuffers, swapChainExtent, graphicsPipeline, renderFinishedSemaphores, graphicsQueue, presentQueue, currentFrame, physicalDevice, surface, window, swapChainImages, swapChainImageFormat, imageCount, swapChainImageViews, vertexBuffer);
    }
    
    vkDeviceWaitIdle(device);

    cleanup(window, device, physicalDevice, instance, surface, swapChain, swapChainImageViews, imageCount, vertShaderModule, fragShaderModule, pipelineLayout, renderPass, graphicsPipeline, swapChainFrameBuffers, commandPool, imageAvailableSemaphores, renderFinishedSemaphores, inFlightFences, vertexBuffer, vertexBufferMemory);

    return 0;
}