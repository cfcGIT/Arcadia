#pragma once

#include "vulkan/vulkan.h"

namespace Arcadia
{
    namespace VKUtils
    {
        std::vector<const char*> GetRequiredExtensions(bool _bValidationLayersEnabled);

        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& oCreateInfo_);

        bool CheckValidationLayerSupport();
    }
}