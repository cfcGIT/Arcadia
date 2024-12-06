#pragma once

#include "vulkan/vulkan.h"

namespace Arcadia
{
    namespace VK
    {
        std::vector<const char*> GetRequiredExtensions(bool _bValidationLayersEnabled);

        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& oCreateInfo_);
    }
}