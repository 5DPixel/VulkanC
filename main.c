#include <stdio.h>

#include "utils/utils.h"
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720
#define WINDOW_NAME "Vulkan Window"

int main()
{
    // VARIABLES
    GLFWwindow *window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    VkImage *swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    VkImageView *swapChainImageViews;
    uint32_t imageCount;
    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    VkFramebuffer *swapChainFrameBuffers;
    VkCommandPool commandPool;
    VkCommandBuffer *commandBuffers;
    VkSemaphore *imageAvailableSemaphores;
    VkSemaphore *renderFinishedSemaphores;
    VkFence *inFlightFences;
    uint32_t currentFrame = 0;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    VkBuffer *uniformBuffers;
    VkDeviceMemory *uniformBuffersMemory;
    void **uniformBuffersMapped;
    VkDescriptorPool descriptorPool;
    VkDescriptorSet *descriptorSets;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    Camera camera;

    GameObject cube;
    GameObject* objects = (GameObject*)malloc(4 * sizeof(GameObject));

    Vertex *vertices;
    uint32_t vertexCount;
    uint32_t *indices;
    uint32_t indexCount;
    
    camera.up = (vec3){0.0f, 0.0f, 1.0f};
    camera.eye = (vec3){2.0f, 2.0f, 2.0f};
    camera.center = (vec3){0.0f, 0.0f, 0.0f};
    camera.fov = 70.0f;
    camera.nearClippingPlane = 0.1f;
    camera.farClippingPlane = 10.0f;
    camera.speed = 0.05f;
    camera.sensitivity = 0.08f;

    objects[0].position = (vec3){1.0f, 1.0f, 1.0f};
    objects[0].rotation = (vec3){0.0f, 0.0f, 0.0f};
    objects[0].scale = (vec3){0.3f, 0.3f, 0.3f};

    objects[1].position = (vec3){1.0f, 3.0f, 1.0f};
    objects[1].rotation = (vec3){0.0f, 0.0f, 0.0f};
    objects[1].scale = (vec3){0.3f, 0.3f, 0.3f};

    objects[2].position = (vec3){3.0f, 1.0f, 1.0f};
    objects[2].rotation = (vec3){0.0f, 0.0f, 0.0f};
    objects[2].scale = (vec3){0.3f, 0.3f, 0.3f};

    objects[3].position = (vec3){3.0f, 3.0f, 1.0f};
    objects[3].rotation = (vec3){0.0f, 0.0f, 0.0f};
    objects[3].scale = (vec3){0.3f, 0.3f, 0.3f};

    initWindow(&window, WIDTH, HEIGHT, WINDOW_NAME);

    printExtensions();
    createInstance(&instance);
    createSurface(instance, window, &surface);
    pickPhysicalDevice(instance, &physicalDevice, &surface);
    createLogicalDevice(&device, &physicalDevice, &graphicsQueue, &presentQueue, &surface);
    createSwapChain(&physicalDevice, &surface, window, &swapChain, &device, &swapChainImages, &swapChainImageFormat, &swapChainExtent, &imageCount);
    createImageViews(&swapChainImageViews, swapChainImages, &swapChainImageFormat, &imageCount, &device);
    createRenderPass(swapChainImageFormat, &renderPass, device, physicalDevice);
    createDescriptorSetLayout(device, &descriptorSetLayout);
    createGraphicsPipeline(&device, swapChainExtent, &pipelineLayout, renderPass, &graphicsPipeline, &vertShaderModule, &fragShaderModule, descriptorSetLayout);
    createCommandPools(&physicalDevice, &commandPool, &surface, device);
    createDepthResources(&depthImage, &depthImageMemory, &depthImageView, physicalDevice, swapChainExtent, device, &swapChainImageViews, commandPool, graphicsQueue);
    createFramebuffers(&swapChainFrameBuffers, swapChainImageViews, imageCount, renderPass, swapChainExtent, device, depthImageView);
    createTextureImage(device, physicalDevice, &textureImage, &textureImageMemory, commandPool, graphicsQueue);
    createTextureImageView(textureImage, &textureImageView, device);
    createTextureSampler(physicalDevice, &textureSampler, device);
    loadModel(&vertices, &vertexCount, &indices, &indexCount);
    createVertexBuffer(vertices, vertexCount, &vertexBuffer, device, physicalDevice, &vertexBufferMemory, commandPool, graphicsQueue);
    createIndexBuffer(indices, indexCount, &indexBuffer, device, physicalDevice, &indexBufferMemory, commandPool, graphicsQueue);
    createUniformBuffers(&uniformBuffers, &uniformBuffersMemory, &uniformBuffersMapped, device, physicalDevice);
    createDescriptorPool(device, &descriptorPool);
    createDescriptorSets(descriptorSetLayout, descriptorPool, &descriptorSets, device, uniformBuffers, textureSampler, textureImageView);
    createCommandBuffers(&commandBuffers, device, commandPool);
    createSyncObjects(device, &imageAvailableSemaphores, &renderFinishedSemaphores, &inFlightFences);

    double lastX = WIDTH / 2, lastY = HEIGHT / 2;
    float yaw = -90.0f, pitch = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        drawFrame(device, inFlightFences, imageAvailableSemaphores, swapChain, commandBuffers, renderPass, swapChainFrameBuffers, swapChainExtent, graphicsPipeline, renderFinishedSemaphores, graphicsQueue, presentQueue, currentFrame, physicalDevice, surface, window, swapChainImages, swapChainImageFormat, imageCount, swapChainImageViews, vertexBuffer, indexBuffer, pipelineLayout, descriptorSets, uniformBuffersMapped, depthImageView, indexCount, &camera, objects, 4);

        if(glfwGetKey(window, GLFW_KEY_W)){
            vec3 direction = normalize(subtract(camera.center, camera.eye));
            camera.eye = add(camera.eye, scale(direction, camera.speed));
            camera.center = add(camera.center, scale(direction, camera.speed));
        }

        if(glfwGetKey(window, GLFW_KEY_S)){
            vec3 direction = normalize(subtract(camera.center, camera.eye));
            camera.eye = subtract(camera.eye, scale(direction, camera.speed));
            camera.center = subtract(camera.center, scale(direction, camera.speed));
        }

        if(glfwGetKey(window, GLFW_KEY_A)){
            vec3 forward = normalize(subtract(camera.center, camera.eye));
            vec3 right = cross(forward, camera.up);
            right = normalize(right);
            camera.eye = subtract(camera.eye, scale(right, camera.speed));
            camera.center = subtract(camera.center, scale(right, camera.speed));
        }

        if(glfwGetKey(window, GLFW_KEY_D)){
            vec3 forward = normalize(subtract(camera.center, camera.eye));
            vec3 right = cross(forward, camera.up);
            right = normalize(right);
            camera.eye = add(camera.eye, scale(right, camera.speed));
            camera.center = add(camera.center, scale(right, camera.speed));
        }

        if(glfwGetKey(window, GLFW_KEY_E)){
            vec3 up = normalize(camera.up);
            camera.eye = add(camera.eye, scale(up, camera.speed));
            camera.center = add(camera.center, scale(up, camera.speed));
        }

        if(glfwGetKey(window, GLFW_KEY_Q)){
            vec3 up = normalize(camera.up);
            camera.eye = subtract(camera.eye, scale(up, camera.speed));
            camera.center = subtract(camera.center, scale(up, camera.speed));
        }

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        float xOffset = (xPos - lastX) * camera.sensitivity;
        float yOffset = (lastY - yPos) * camera.sensitivity;

        lastX = xPos;
        lastY = yPos;

        yaw -= xOffset;
        pitch += yOffset;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        vec3 direction;
        direction.x = cosf(deg2Rad(yaw)) * cosf(deg2Rad(pitch));
        direction.z = sinf(deg2Rad(pitch));
        direction.y = sinf(deg2Rad(yaw)) * cosf(deg2Rad(pitch));
        direction = normalize(direction);

        camera.center = add(camera.eye, direction);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    vkDeviceWaitIdle(device);

    cleanup(window, device, physicalDevice, instance, surface, swapChain, swapChainImageViews, imageCount, vertShaderModule, fragShaderModule, pipelineLayout, renderPass, graphicsPipeline, swapChainFrameBuffers, commandPool, imageAvailableSemaphores, renderFinishedSemaphores, inFlightFences, vertexBuffer, vertexBufferMemory, indexBuffer, indexBufferMemory, descriptorSetLayout, uniformBuffers, uniformBuffersMemory, descriptorPool, textureImage, textureImageMemory, textureImageView, textureSampler, depthImage, depthImageView, depthImageMemory);

    return 0;
}