#pragma once

namespace Arcadia
{
    namespace VKUtils
    {
        std::vector<const char*> GetRequiredExtensions(bool _bValidationLayersEnabled);

        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& oVKCreateInfo_);

        bool CheckValidationLayerSupport();

        std::string GetVersionString(uint32_t _uVersion);
    }
}