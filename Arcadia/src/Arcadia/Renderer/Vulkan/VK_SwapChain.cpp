#include "Arcadia/Renderer/Vulkan/VK_SwapChain.h"

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_Image.h"
#include "Arcadia/Renderer/Vulkan/VK_LogicalDevice.h"
#include "Arcadia/Renderer/Vulkan/VK_PhysicalDevice.h"
#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"
#include "Arcadia/Renderer/Vulkan/VK_Surface.h"
#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace Arcadia
{
    namespace VK
    {
        /**
        * @brief Choose the surface format (color depth)
        */
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& _tVKAvailableFormats)
        {
            // The format member specifies the color channels and types.
            // The colorSpace member indicates if the SRGB color space is supported or not using the VK_COLOR_SPACE_SRGB_NONLINEAR_KHR flag
            for (const VkSurfaceFormatKHR& oVKAvailableFormat : _tVKAvailableFormats)
            {
                if (oVKAvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && oVKAvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                {
                    return oVKAvailableFormat;
                }
            }

            return _tVKAvailableFormats[0];
        }

        /**
        * @brief Choose the presentation mode (conditions for "swapping" images to the screen)
        */
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& _tVKAvailablePresentModes)
        {
            // TODO: VK_PRESENT_MODE_FIFO_KHR if vsync?
            // TODO: VK_PRESENT_MODE_IMMEDIATE_KHR if VK_PRESENT_MODE_MAILBOX_KHR is not available?
            for (const VkPresentModeKHR& oVKAvailablePresentMode : _tVKAvailablePresentModes)
            {
                if (oVKAvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) // VK_PRESENT_MODE_MAILBOX_KHR allows us to avoid tearing while still maintaining a fairly low latency by rendering new images that are as up-to-date as possible right until the vertical blank
                {
                    return oVKAvailablePresentMode;
                }
            }

            return VK_PRESENT_MODE_FIFO_KHR; // Only the VK_PRESENT_MODE_FIFO_KHR mode is guaranteed to be available
        }

        /**
        * @brief Choose the swap extent (resolution of images in swap chain, that it's almost always exactly equal to the resolution of the window that we're drawing to in pixels)
        */
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& _oVKCapabilities)
        {
            // The resolution {WIDTH, HEIGHT} that we specified earlier when creating the window is measured in screen coordinates. But Vulkan works with pixels, so the swap chain extent must be specified in pixels as well
            if (_oVKCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
            {
                return _oVKCapabilities.currentExtent;
            }
            else
            {
                int iWidth = 0;
                int iHeight = 0;
                // We must use glfwGetFramebufferSize to query the resolution of the window in pixel before matching it against the minimum and maximum image extent
                glfwGetFramebufferSize(Arcadia::CWindow::GetGLFWwindow(), &iWidth, &iHeight);

                VkExtent2D oVKActualExtent = {
                    static_cast<uint32_t>(iWidth),
                    static_cast<uint32_t>(iHeight)
                };

                oVKActualExtent.width = glm::clamp(oVKActualExtent.width, _oVKCapabilities.minImageExtent.width, _oVKCapabilities.maxImageExtent.width);
                oVKActualExtent.height = glm::clamp(oVKActualExtent.height, _oVKCapabilities.minImageExtent.height, _oVKCapabilities.maxImageExtent.height);

                return oVKActualExtent;
            }
        }

        // ---------

        CVK_SwapChain::CVK_SwapChain()
        {
            // Choose the right settings for the swap chain
            SSwapChainSupportDetails oSwapChainSupport = QuerySwapChainSupport(Arcadia::VK::CVK_PhysicalDevice::GetVKPhysicalDevice());
            VkSurfaceFormatKHR oVKSurfaceFormat = Arcadia::VK::ChooseSwapSurfaceFormat(oSwapChainSupport.m_tVKFormats);
            VkPresentModeKHR oVKPresentMode = Arcadia::VK::ChooseSwapPresentMode(oSwapChainSupport.m_tVKPresentModes);
            VkExtent2D oVKExtent = Arcadia::VK::ChooseSwapExtent(oSwapChainSupport.m_oVKCapabilities);

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
                m_tVKSwapChainImageViews[i] = Arcadia::VK::CreateImageView(m_tVKSwapChainImages[i], m_oVKSwapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
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