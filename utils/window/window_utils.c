#include "window_utils.h"

void initWindow(GLFWwindow** window, int width, int height, char* windowName){
    if (!glfwInit()) {
        printf("Failed to initialize GLFW!\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    *window = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (!*window) {
        printf("Failed to create GLFW window!\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void printExtensions(){
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);

    VkExtensionProperties* extensions = (VkExtensionProperties*)malloc(extensionCount * sizeof(VkExtensionProperties));

    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensions);

    printf("%u extensions supported\n", extensionCount);

        for (uint32_t i = 0; i < extensionCount; i++) {
        printf("%s\n", extensions[i].extensionName);
    }

    free(extensions);
}

bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);

    VkLayerProperties* availableLayers = (VkLayerProperties*)malloc(layerCount * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

    if (availableLayers == NULL) {
        return false;
    }

    bool layerFound = false;
    for (uint32_t j = 0; j < layerCount; ++j) {
        if (strcmp(validationLayers[0], availableLayers[j].layerName) == 0) {
            printf("Found validation layer: %s", availableLayers[j].layerName);
            layerFound = true;
            break;
        }
    }

    free(availableLayers);
    return layerFound;
}

const char** getRequiredExtensions(uint32_t* count) {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    uint32_t maxExtensions = glfwExtensionCount + 1;
    const char** extensions = malloc(maxExtensions * sizeof(char*));
    if (!extensions) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        extensions[i] = glfwExtensions[i];
    }

    extensions[glfwExtensionCount] = "VK_EXT_debug_utils";
    *count = maxExtensions;

    return extensions;
}