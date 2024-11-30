#pragma once

#include "vulkan/vulkan.h"

namespace Arcadia::VK
{
    std::vector<const char*> GetRequiredExtensions(bool _bValidationLayersEnabled);

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo_);
}