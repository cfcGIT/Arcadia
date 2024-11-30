#pragma once

#include "Arcadia/Log.h"
#include "Arcadia/Renderer/Vulkan/VK_Error.h"

#include "GLFW/glfw3.h"

/**
* TODO: Class?
*/

namespace Arcadia::VK
{
    const bool bVKDebug =
#ifdef ARC_VK_DEBUG
        true;
#else
        false;
#endif
    const std::vector<const char*> vValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    // Create vulkan instance
    VkResult CreateInstance(VkInstance& instance_);
}