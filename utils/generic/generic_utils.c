#include "generic_utils.h"

void createInstance(VkInstance* instance){
    if (!checkValidationLayerSupport()) {
        printf("validation layers requested, but not available!");
    }

    VkApplicationInfo appInfo = {0};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan App";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledLayerCount = sizeof(validationLayers) / sizeof(validationLayers[0]);
    createInfo.ppEnabledLayerNames = validationLayers;

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {0};

    uint32_t extensionCount = 0;
    const char** extensions = getRequiredExtensions(&extensionCount);
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;

    if (vkCreateInstance(&createInfo, NULL, instance) != VK_SUCCESS) {
        printf("failed to create Vulkan instance!\n");
    }
}

void cleanup(GLFWwindow* window, VkDevice device, VkPhysicalDevice physicalDevice, VkInstance instance, VkSurfaceKHR surface, VkSwapchainKHR swapChain, VkImageView* swapChainImageViews, uint32_t swapChainImageViewCount, VkShaderModule vertShaderModule, VkShaderModule fragShaderModule, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, VkPipeline graphicsPipeline, VkFramebuffer* swapChainFrameBuffers, VkCommandPool commandPool, VkSemaphore* imageAvailableSemaphores, VkSemaphore* renderFinishedSemaphores, VkFence* inFlightFences, VkBuffer vertexBuffer, VkDeviceMemory vertexBufferMemory, VkBuffer indexBuffer, VkDeviceMemory indexBufferMemory, VkDescriptorSetLayout descriptorSetLayout, VkBuffer* uniformBuffers, VkDeviceMemory* uniformBuffersMemory, VkDescriptorPool descriptorPool, VkImage textureImage, VkDeviceMemory textureImageMemory){    
    vkFreeMemory(device, textureImageMemory, NULL);
    vkDestroyImage(device, textureImage, NULL);
    
    vkDestroyDescriptorPool(device, descriptorPool, NULL);
    
    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++){
        vkDestroyBuffer(device, uniformBuffers[i], NULL);
        vkFreeMemory(device, uniformBuffersMemory[i], NULL);
    }
    
    vkDestroyBuffer(device, vertexBuffer, NULL);
    vkFreeMemory(device, vertexBufferMemory, NULL);

    vkDestroyBuffer(device, indexBuffer, NULL);
    vkFreeMemory(device, indexBufferMemory, NULL);

    vkDestroyPipeline(device, graphicsPipeline, NULL);

    vkDestroyPipelineLayout(device, pipelineLayout, NULL);
    vkDestroyDescriptorSetLayout(device, descriptorSetLayout, NULL);
    vkDestroyRenderPass(device, renderPass, NULL);
    
    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++){
        vkDestroySemaphore(device, imageAvailableSemaphores[i], NULL);
        vkDestroySemaphore(device, renderFinishedSemaphores[i], NULL);
        vkDestroyFence(device, inFlightFences[i], NULL);
    }

    vkDestroyCommandPool(device, commandPool, NULL);

    for(uint32_t i = 0; i < swapChainImageViewCount; i++){
        vkDestroyFramebuffer(device, swapChainFrameBuffers[i], NULL);
    }

    vkDestroyShaderModule(device, fragShaderModule, NULL);
    vkDestroyShaderModule(device, vertShaderModule, NULL);
    for(uint32_t i = 0; i < swapChainImageViewCount; i++){
        vkDestroyImageView(device, swapChainImageViews[i], NULL);
    }

    vkDestroySwapchainKHR(device, swapChain, NULL);
    vkDestroySurfaceKHR(instance, surface, NULL);
    vkDestroyDevice(device, NULL);
    vkDestroyInstance(instance, NULL);

    glfwDestroyWindow(window);

    glfwTerminate();
}

void createSyncObjects(VkDevice device, VkSemaphore** imageAvailableSemaphores, VkSemaphore** renderFinishedSemaphores, VkFence** inFlightFences){
    *imageAvailableSemaphores = (VkSemaphore*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));
    *renderFinishedSemaphores = (VkSemaphore*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkSemaphore));
    *inFlightFences = (VkFence*)malloc(MAX_FRAMES_IN_FLIGHT * sizeof(VkFence));

    VkSemaphoreCreateInfo semaphoreInfo = {0};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo = {0};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++){
        if(vkCreateSemaphore(device, &semaphoreInfo, NULL, &(*imageAvailableSemaphores)[i]) != VK_SUCCESS || vkCreateSemaphore(device, &semaphoreInfo, NULL, &(*renderFinishedSemaphores)[i]) != VK_SUCCESS || vkCreateFence(device, &fenceInfo, NULL, &(*inFlightFences)[i]) != VK_SUCCESS){
            fprintf(stderr, "failed to create semaphores and or fences!\n");
        }
    }
}