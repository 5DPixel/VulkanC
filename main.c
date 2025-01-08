#include <stdio.h>

#include "utils/utils.h"

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
    VkDescriptorSetLayout descriptorSetLayout;
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
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer* uniformBuffers;
    VkDeviceMemory* uniformBuffersMemory;
    void** uniformBuffersMapped;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet* descriptorSets;

    Vertex vertices[4] = {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
    };

    uint16_t indices[] = {
        0, 1, 2, 2, 3, 0
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
    createDescriptorSetLayout(device, &descriptorSetLayout);
    createGraphicsPipeline(&device, swapChainExtent, &pipelineLayout, renderPass, &graphicsPipeline, &vertShaderModule, &fragShaderModule, descriptorSetLayout);
    createFramebuffers(&swapChainFrameBuffers, swapChainImageViews, imageCount, renderPass, swapChainExtent, device);
    createCommandPools(&physicalDevice, &commandPool, &surface, device);
    createVertexBuffer(vertices, 4, &vertexBuffer, device, physicalDevice, &vertexBufferMemory, commandPool, graphicsQueue);
    createIndexBuffer(indices, 6, &indexBuffer, device, physicalDevice, &indexBufferMemory, commandPool, graphicsQueue);
    createUniformBuffers(&uniformBuffers, &uniformBuffersMemory, &uniformBuffersMapped, device, physicalDevice);
    createDescriptorPool(device, &descriptorPool);
    createDescriptorSets(descriptorSetLayout, descriptorPool, &descriptorSets, device, uniformBuffers);
    createCommandBuffers(&commandBuffers, device, commandPool);
    createSyncObjects(device, &imageAvailableSemaphores, &renderFinishedSemaphores, &inFlightFences);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame(device, inFlightFences, imageAvailableSemaphores, swapChain, commandBuffers, renderPass, swapChainFrameBuffers, swapChainExtent, graphicsPipeline, renderFinishedSemaphores, graphicsQueue, presentQueue, currentFrame, physicalDevice, surface, window, swapChainImages, swapChainImageFormat, imageCount, swapChainImageViews, vertexBuffer, indexBuffer, pipelineLayout, descriptorSets, uniformBuffersMapped);
    }
    
    vkDeviceWaitIdle(device);

    cleanup(window, device, physicalDevice, instance, surface, swapChain, swapChainImageViews, imageCount, vertShaderModule, fragShaderModule, pipelineLayout, renderPass, graphicsPipeline, swapChainFrameBuffers, commandPool, imageAvailableSemaphores, renderFinishedSemaphores, inFlightFences, vertexBuffer, vertexBufferMemory, indexBuffer, indexBufferMemory, descriptorSetLayout, uniformBuffers, uniformBuffersMemory, descriptorPool);

    return 0;
}