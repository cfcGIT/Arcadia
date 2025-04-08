#pragma once

namespace Arcadia
{
    namespace VK
    {
        class CVK_Surface;

        class CVK_SwapChain
        {
        public:
            struct SSwapChainSupportDetails
            {
                VkSurfaceCapabilitiesKHR m_oVKCapabilities;
                std::vector<VkSurfaceFormatKHR> m_tVKFormats;
                std::vector<VkPresentModeKHR> m_tVKPresentModes;
            };

        public:
            CVK_SwapChain();
            ~CVK_SwapChain();

            inline VkSwapchainKHR GetVulkanSwapChain() const { return m_oVKSwapChain; }

        private:
            SSwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice _oVKPhysicalDevice);

        private:
            VkSwapchainKHR m_oVKSwapChain = VK_NULL_HANDLE;
            std::vector<VkImage> m_tVKSwapChainImages = std::vector<VkImage>();
            std::vector<VkImageView> m_tVKSwapChainImageViews = std::vector<VkImageView>();
            VkFormat m_oVKSwapChainImageFormat = VK_FORMAT_UNDEFINED;
            VkExtent2D m_oVKSwapChainExtent = VkExtent2D(0, 0);
        };
    }
}