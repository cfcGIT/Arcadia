#pragma once

namespace Arcadia
{
    namespace VKUtils
    {
        std::vector<const char*> GetRequiredExtensions(bool _bValidationLayersEnabled);

        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& oVKCreateInfo_);

        bool CheckValidationLayerSupport();

        // Utils to create the swap chain
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _tVKAvailableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _tVKAvailablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _oVKCapabilities);
        VkImageView CreateImageView(const VkImage& _oImage, const VkFormat& _oFormat, const VkImageAspectFlags& _oAspectFlags, const uint32_t _uMipLevels);

        std::string GetVersionString(uint32_t _uVersion);
    }
}