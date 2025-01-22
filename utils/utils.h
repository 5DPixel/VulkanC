#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32

#include "buffer/buffer_utils.h"
#include "constants_and_arrays/constants_and_arrays.h"
#include "device_and_surface/device_utils.h"
#include "generic/generic_utils.h"
#include "graphics/graphics_utils.h"
#include "swapchain/swapchain_utils.h"
#include "window/window_utils.h"
#include "../math/math_utils.h"
#include "../math/hash_map.h"