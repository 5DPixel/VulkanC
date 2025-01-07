#include "swapchain_utils.h"

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice* device, VkSurfaceKHR* surface){
    SwapChainSupportDetails details;
    details.formatCount = -1;
    details.presentModeCount = -1;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*device, *surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(*device, *surface, &formatCount, NULL);

    if(formatCount != 0){
        details.formats = (VkSurfaceFormatKHR*)malloc(formatCount * sizeof(VkSurfaceFormatKHR));
        details.formatCount = formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(*device, *surface, &formatCount, details.formats);
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(*device, *surface, &presentModeCount, NULL);

    if(presentModeCount != 0){
        details.presentModes = (VkPresentModeKHR*)malloc(presentModeCount * sizeof(VkPresentModeKHR));
        details.presentModeCount = presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(*device, *surface, &presentModeCount, details.presentModes);
    }

    return details;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR* availableFormats, uint32_t formatCount){
    for(uint32_t i = 0; i < formatCount; i++){
        if(availableFormats[i].format == VK_FORMAT_B8G8R8A8_SRGB && availableFormats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
            return availableFormats[i];
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR* availablePresentModes, uint32_t presentModeCount){
    for(uint32_t i = 0; i < presentModeCount; i++){
        if(availablePresentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR){
            printf("Using present mode: MAILBOX\n");
            return availablePresentModes[i];
        }
    }

    printf("Using present mode: FIFO\n");
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D chooseSwapExtent(VkSurfaceCapabilitiesKHR capabilities, GLFWwindow* window){
    if(capabilities.currentExtent.width != UINT32_MAX){
        return capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = {
            (uint32_t)width,
            (uint32_t)height
        };
     
        actualExtent.width = clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

void createSwapChain(VkPhysicalDevice* physicalDevice, VkSurfaceKHR* surface, GLFWwindow* window, VkSwapchainKHR* swapChain, VkDevice* device, VkImage** swapChainImages, VkFormat* swapChainImageFormat, VkExtent2D* swapChainExtent, uint32_t* imageCount){
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surface);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats, swapChainSupport.formatCount);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes, swapChainSupport.presentModeCount);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities, window);

    *imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if(swapChainSupport.capabilities.maxImageCount > 0 && *imageCount > swapChainSupport.capabilities.maxImageCount){
        *imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = *surface;

    createInfo.minImageCount = *imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};

    if(indices.graphicsFamily != indices.presentFamily){
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = NULL; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    *swapChainImageFormat = surfaceFormat.format;
    *swapChainExtent = extent;

    if(vkCreateSwapchainKHR(*device, &createInfo, NULL, swapChain) != VK_SUCCESS){
        fprintf(stderr, "failed to create swap chain!");
    }
    
    vkGetSwapchainImagesKHR(*device, *swapChain, imageCount, NULL);
    *swapChainImages = (VkImage*)malloc(*imageCount * sizeof(VkImage));

    if (*swapChainImages == NULL) {
        fprintf(stderr, "failed to allocate memory for swap chain images!");
        return;
    }

    vkGetSwapchainImagesKHR(*device, *swapChain, imageCount, *swapChainImages);
}

void createImageViews(VkImageView** swapChainImageViews, VkImage* swapChainImages, VkFormat* swapChainImageFormat, uint32_t* imageCount, VkDevice* device){
    *swapChainImageViews = (VkImageView*)malloc(*imageCount * sizeof(VkImageView));

    for(size_t i = 0; i < *imageCount; i++){
        VkImageViewCreateInfo createInfo = {0};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];

        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = *swapChainImageFormat;

        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if(vkCreateImageView(*device, &createInfo, NULL, &(*swapChainImageViews)[i]) != VK_SUCCESS){
            fprintf(stderr, "failed to create image views!");
        }
    }
}

void createFramebuffers(VkFramebuffer** swapChainFrameBuffers, VkImageView* swapChainImageViews, uint32_t imageCount, VkRenderPass renderPass, VkExtent2D swapChainExtent, VkDevice device){
    *swapChainFrameBuffers = (VkFramebuffer*)malloc(imageCount * sizeof(VkFramebuffer));

    for(size_t i = 0; i < imageCount; i++){
        VkImageView attachments[] = {
            swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo = {0};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if(vkCreateFramebuffer(device, &framebufferInfo, NULL, &(*swapChainFrameBuffers)[i]) != VK_SUCCESS){
            fprintf(stderr, "failed to create framebuffer!");
        }
    }
}

void recreateSwapChain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window, VkSwapchainKHR swapChain, VkImage* swapChainImages, VkFormat swapChainImageFormat, VkExtent2D swapChainExtent, uint32_t imageCount, VkImageView* swapChainImageViews, VkFramebuffer* swapChainFramebuffers, VkRenderPass renderPass){
    vkDeviceWaitIdle(device);

    createSwapChain(&physicalDevice, &surface, window, &swapChain, &device, &swapChainImages, &swapChainImageFormat, &swapChainExtent, &imageCount);
    createImageViews(&swapChainImageViews, swapChainImages, &swapChainImageFormat, &imageCount, &device);
    createFramebuffers(&swapChainFramebuffers, swapChainImageViews, imageCount, renderPass, swapChainExtent, device); 
}