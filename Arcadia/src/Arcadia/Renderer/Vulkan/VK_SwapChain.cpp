#include "Arcadia/Renderer/Vulkan/VK_SwapChain.h"

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_LogicalDevice.h"
#include "Arcadia/Renderer/Vulkan/VK_PhysicalDevice.h"
#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"
#include "Arcadia/Renderer/Vulkan/VK_Surface.h"
#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    namespace VK
    {
        CVK_SwapChain::CVK_SwapChain()
        {
            // Choose the right settings for the swap chain
            SSwapChainSupportDetails oSwapChainSupport = QuerySwapChainSupport(Arcadia::VK::CVK_PhysicalDevice::GetVKPhysicalDevice());
            VkSurfaceFormatKHR oVKSurfaceFormat = Arcadia::VKUtils::ChooseSwapSurfaceFormat(oSwapChainSupport.m_tVKFormats);
            VkPresentModeKHR oVKPresentMode = Arcadia::VKUtils::ChooseSwapPresentMode(oSwapChainSupport.m_tVKPresentModes);
            VkExtent2D oVKExtent = Arcadia::VKUtils::ChooseSwapExtent(oSwapChainSupport.m_oVKCapabilities);

            m_oVKSwapChainImageFormat = oVKSurfaceFormat.format;
            m_oVKSwapChainExtent = oVKExtent;

            // How many images we would like to have in the swap chain
            uint32_t uImageCount = oSwapChainSupport.m_oVKCapabilities.minImageCount + 1;
            // We should also make sure to not exceed the maximum number of images while doing this, where 0 is a special value that means that there is no maximum
            if (oSwapChainSupport.m_oVKCapabilities.maxImageCount > 0 && uImageCount > oSwapChainSupport.m_oVKCapabilities.maxImageCount)
            {
                uImageCount = oSwapChainSupport.m_oVKCapabilities.maxImageCount;
            }

            // Creation of the swap chain
            VkSwapchainCreateInfoKHR createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.surface = Arcadia::VK::CVK_Surface::GetVKSurface();
            createInfo.minImageCount = uImageCount;
            createInfo.imageFormat = oVKSurfaceFormat.format;
            createInfo.imageColorSpace = oVKSurfaceFormat.colorSpace;
            createInfo.imageExtent = oVKExtent;
            createInfo.imageArrayLayers = 1;
            createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            // TODO: Vulkan tutorial uses VK_SHARING_MODE_CONCURRENT when the graphics queue family is different from the presentation queue (https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain#page_Choosing-the-right-settings-for-the-swap-chain)
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;

            // We can specify that a certain transform should be applied to images in the swap chain if it is supported (supportedTransforms in capabilities), like a 90 degree clockwise rotation or horizontal flip. To specify that you do not want any transformation, simply specify the current transformation
            createInfo.preTransform = oSwapChainSupport.m_oVKCapabilities.currentTransform;
            // The compositeAlpha field specifies if the alpha channel should be used for blending with other windows in the window system. You'll almost always want to simply ignore the alpha channel, hence VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR
            createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

            createInfo.presentMode = oVKPresentMode;
            createInfo.clipped = VK_TRUE; // that means that we don't care about the color of pixels that are obscured, for example because another window is in front of them. Unless you really need to be able to read these pixels back and get predictable results, you'll get the best performance by enabling clipping

            createInfo.oldSwapchain = VK_NULL_HANDLE;

            ARC_VK_CHECK(vkCreateSwapchainKHR(Arcadia::VK::CVK_LogicalDevice::GetVKDevice(), &createInfo, nullptr, &m_oVKSwapChain), "Failed to create swap chain!");

            // Retrieving the swap chain images
            vkGetSwapchainImagesKHR(Arcadia::VK::CVK_LogicalDevice::GetVKDevice(), m_oVKSwapChain, &uImageCount, nullptr);
            m_tVKSwapChainImages.resize(uImageCount);
            vkGetSwapchainImagesKHR(Arcadia::VK::CVK_LogicalDevice::GetVKDevice(), m_oVKSwapChain, &uImageCount, m_tVKSwapChainImages.data());

            // Create swap chain image views
            m_tVKSwapChainImageViews.resize(uImageCount);
            for (uint32_t i = 0; i < uImageCount; ++i)
            {
                m_tVKSwapChainImageViews[i] = Arcadia::VKUtils::CreateImageView(m_tVKSwapChainImages[i], m_oVKSwapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
            }
        }

        CVK_SwapChain::~CVK_SwapChain()
        {
            // Destroy swap chain image views
            uint32_t uSizeImageViews = m_tVKSwapChainImageViews.size();
            for (uint32_t i = 0; i < uSizeImageViews; ++i)
            {
                vkDestroyImageView(Arcadia::VK::CVK_LogicalDevice::GetVKDevice(), m_tVKSwapChainImageViews[i], nullptr);
            }
            // Destroy swap chain
            vkDestroySwapchainKHR(Arcadia::VK::CVK_LogicalDevice::GetVKDevice(), m_oVKSwapChain, nullptr);
        }

        /**
        * @brief Check basic surface capabilities, surface formats and available presentation modes
        */
        CVK_SwapChain::SSwapChainSupportDetails CVK_SwapChain::QuerySwapChainSupport(VkPhysicalDevice _oVKPhysicalDevice)
        {
            SSwapChainSupportDetails oDetails;

            // Basic surface capabilities (min/max number of images in swap chain, min/max width and height of images)
            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_oVKPhysicalDevice, Arcadia::VK::CVK_Surface::GetVKSurface(), &oDetails.m_oVKCapabilities);

            // Surface formats (pixel format, color space)
            uint32_t uFormatCount;
            vkGetPhysicalDeviceSurfaceFormatsKHR(_oVKPhysicalDevice, Arcadia::VK::CVK_Surface::GetVKSurface(), &uFormatCount, nullptr);
            if (uFormatCount != 0)
            {
                oDetails.m_tVKFormats.resize(uFormatCount);
                vkGetPhysicalDeviceSurfaceFormatsKHR(_oVKPhysicalDevice, Arcadia::VK::CVK_Surface::GetVKSurface(), &uFormatCount, oDetails.m_tVKFormats.data());
            }

            // Available presentation modes
            uint32_t uPresentModeCount;
            vkGetPhysicalDeviceSurfacePresentModesKHR(_oVKPhysicalDevice, Arcadia::VK::CVK_Surface::GetVKSurface(), &uPresentModeCount, nullptr);
            if (uPresentModeCount != 0)
            {
                oDetails.m_tVKPresentModes.resize(uPresentModeCount);
                vkGetPhysicalDeviceSurfacePresentModesKHR(_oVKPhysicalDevice, Arcadia::VK::CVK_Surface::GetVKSurface(), &uPresentModeCount, oDetails.m_tVKPresentModes.data());
            }

            return oDetails;
        }
    }
}