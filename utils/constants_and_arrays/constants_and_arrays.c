#include "constants_and_arrays.h"

const char* validationLayers[1] = {
    "VK_LAYER_KHRONOS_validation"
};

const char* deviceExtensions[1] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

bool assertVertexStructsEqual(Vertex v1, Vertex v2){
    return (
        v1.pos.x == v2.pos.x &&
        v1.pos.y == v2.pos.y &&
        v1.pos.z == v2.pos.z &&

        v1.color.x == v2.color.x &&
        v1.color.y == v2.color.y &&
        v1.color.z == v2.color.z &&

        v1.texCoord.x == v2.texCoord.x &&
        v1.texCoord.y == v2.texCoord.y
    );
}