#include "device_utils.h"
#include <stdio.h>

void pickPhysicalDevice(VkInstance instance, VkPhysicalDevice *physicalDevice, VkSurfaceKHR* surface){
    *physicalDevice = VK_NULL_HANDLE;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    if (deviceCount == 0) {
        fprintf(stderr, "failed to find GPUs with Vulkan support!");
    }

    VkPhysicalDevice* devices = (VkPhysicalDevice*)malloc(deviceCount * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    for(uint32_t i = 0; i < deviceCount; i++){
        if(isDeviceSuitable(&devices[i], surface)){
            *physicalDevice = devices[i];

            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(*physicalDevice, &deviceProperties);
            printf("\nSelected physical device: %s\n", deviceProperties.deviceName);

            break;
        }
    }

    free(devices);

    if (physicalDevice == VK_NULL_HANDLE) {
        fprintf(stderr, "failed to find a suitable GPU!\n");
    }
}

bool isDeviceSuitable(VkPhysicalDevice* device, VkSurfaceKHR* surface){
    QueueFamilyIndices indices = findQueueFamilies(device, surface);
    bool swapChainAdequate = false;

    if(indices.graphicsFamily != -1){
        return true;
    } else {
        return false;
    }

    return (indices.graphicsFamily != INVALID_FAMILY_INDEX && indices.presentFamily != INVALID_FAMILY_INDEX) && swapChainAdequate;
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice* device, VkSurfaceKHR* surface) {
    QueueFamilyIndices indices = {INVALID_FAMILY_INDEX, INVALID_FAMILY_INDEX};

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(*device, &queueFamilyCount, NULL);

    VkQueueFamilyProperties* queueFamilies = (VkQueueFamilyProperties*)malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(*device, &queueFamilyCount, queueFamilies);

    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        if (indices.graphicsFamily == INVALID_FAMILY_INDEX && (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(*device, i, *surface, &presentSupport);
        
        if (presentSupport) {
            indices.presentFamily = i;
        }

        if (indices.graphicsFamily != INVALID_FAMILY_INDEX && indices.presentFamily != INVALID_FAMILY_INDEX) {
            break;
        }
    }

    free(queueFamilies);

    return indices;
}

void createSurface(VkInstance instance, GLFWwindow* window, VkSurfaceKHR* surface){
    if(glfwCreateWindowSurface(instance, window, NULL, surface) != VK_SUCCESS){
        fprintf(stderr, "failed to create window surface!");
    }
}

bool checkDeviceExtensionSupport(VkPhysicalDevice* device){
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(*device, NULL, &extensionCount, NULL);

    VkExtensionProperties* availableExtensions = (VkExtensionProperties*)malloc(extensionCount * sizeof(VkExtensionProperties));
    vkEnumerateDeviceExtensionProperties(*device, NULL, &extensionCount, availableExtensions);

    const char* requiredExtensions = deviceExtensions[0];

    for(uint32_t i = 0; i < extensionCount; i++){
        requiredExtensions = 0;
    }

    if(requiredExtensions == NULL){
        return true;
    } else {
        return false;
    }

    return false;
}

void createLogicalDevice(VkDevice* device, VkPhysicalDevice* physicalDevice, VkQueue* graphicsQueue, VkQueue* presentQueue, VkSurfaceKHR* surface){
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);

    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo* queueCreateInfos = NULL;
    size_t queueCreateInfoCount = 0;

    uint32_t* uniqueQueueFamilies = NULL;
    size_t uniqueQueueFamiliesCount = 0;

    if (indices.graphicsFamily != INVALID_FAMILY_INDEX) {
        uniqueQueueFamilies = realloc(uniqueQueueFamilies, (uniqueQueueFamiliesCount + 1) * sizeof(uint32_t));
        uniqueQueueFamilies[uniqueQueueFamiliesCount++] = indices.graphicsFamily;
    }

    if (indices.presentFamily != INVALID_FAMILY_INDEX) {
        bool alreadyAdded = false;
        for (size_t i = 0; i < uniqueQueueFamiliesCount; ++i) {
            if (uniqueQueueFamilies[i] == indices.presentFamily) {
                alreadyAdded = true;
                break;
            }
        }
        if (!alreadyAdded) {
            uniqueQueueFamilies = realloc(uniqueQueueFamilies, (uniqueQueueFamiliesCount + 1) * sizeof(uint32_t));
            uniqueQueueFamilies[uniqueQueueFamiliesCount++] = indices.presentFamily;
        }
    }

    for (size_t i = 0; i < uniqueQueueFamiliesCount; ++i) {
        VkDeviceQueueCreateInfo queueCreateInfo = {0};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = uniqueQueueFamilies[i];
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
    
        queueCreateInfos = realloc(queueCreateInfos, (queueCreateInfoCount + 1) * sizeof(VkDeviceQueueCreateInfo));
        queueCreateInfos[queueCreateInfoCount++] = queueCreateInfo;
    }

    free(uniqueQueueFamilies);

    VkPhysicalDeviceFeatures deviceFeatures = {0};

    VkDeviceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = queueCreateInfos;
    createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfoCount;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 1;
    createInfo.ppEnabledExtensionNames = deviceExtensions;
    createInfo.enabledLayerCount = 1;
    createInfo.ppEnabledLayerNames = validationLayers;

    if(vkCreateDevice(*physicalDevice, &createInfo, NULL, device) != VK_SUCCESS){
        fprintf(stderr, "failed to create logical device!");
    }

    vkGetDeviceQueue(*device, indices.graphicsFamily, 0, graphicsQueue);
    vkGetDeviceQueue(*device, indices.presentFamily, 0, presentQueue);

    free(queueCreateInfos);
}