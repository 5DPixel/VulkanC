cmake_minimum_required(VERSION 3.28)

project(VulkanApp VERSION 1.0 LANGUAGES C)

set(VULKAN_SDK "C:/VulkanSDK/1.3.296.0")
set(CMAKE_GENERATOR_PLATFORM x64)

set(CMAKE_BUILD_TYPE Release)

include_directories(${VULKAN_SDK}/include)
link_directories(${VULKAN_SDK}/lib)

set(GLFW_PATH "C:/Users/judet/OneDrive/Documents/Libraries/glfw-3.4.bin.WIN64/glfw-3.4.bin.WIN64")

include_directories(${GLFW_PATH}/include)
link_directories(${GLFW_PATH}/lib)

add_executable(
    VulkanApp 
    main.c
    file/file_utils.c
    math/math_utils.c
    math/hash_map.c
    utils/buffer/buffers_utils.c
    utils/constants_and_arrays/constants_and_arrays.c
    utils/device_and_surface/device_utils.c
    utils/generic/generic_utils.c
    utils/graphics/graphics_utils.c
    utils/swapchain/swapchain_utils.c
    utils/window/window_utils.c
    image/stb_image.h
    obj/obj_loader.c
)
target_link_libraries(VulkanApp ${VULKAN_SDK}/lib/vulkan-1.lib ${GLFW_PATH}/lib-vc2022/glfw3.lib)