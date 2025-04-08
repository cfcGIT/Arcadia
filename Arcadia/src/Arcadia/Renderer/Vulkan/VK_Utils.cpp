#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_LogicalDevice.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace Arcadia
{
    namespace VKUtils
    {
        // For doxygen doc
        /** @defgroup VKUtilsGroup VK_Utils
         *  VK_Utils group
         *  @{
         */

        /**
        * @brief Will return the required list of extensions based on whether validation layers are enabled or not
        */
        std::vector<const char*> GetRequiredExtensions(bool _bValidationLayersEnabled)
        {
            uint32_t uGlfwExtensionCount = 0;
            const char** pGlfwExtensions;
            pGlfwExtensions = glfwGetRequiredInstanceExtensions(&uGlfwExtensionCount); // e.g.: "VK_KHR_surface" & "VK_KHR_win32_surface"

            std::vector<const char*> tExtensions(pGlfwExtensions, pGlfwExtensions + uGlfwExtensionCount);

            if (_bValidationLayersEnabled)
            {
                tExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            return tExtensions;
        }

        /**
        * @brief Create debug messenger to handle validation layers messages
        */
        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& oVKCreateInfo_)
        {
            oVKCreateInfo_ = {};
            oVKCreateInfo_.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            oVKCreateInfo_.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            oVKCreateInfo_.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            oVKCreateInfo_.pfnUserCallback = Arcadia::VK::DebugCallback;
            oVKCreateInfo_.pUserData = nullptr; // Optional
        }

        /**
        * @brief Check that all of the validation layers exist in the available layers list
        */
        bool CheckValidationLayerSupport()
        {
            uint32_t uLayerCount;
            vkEnumerateInstanceLayerProperties(&uLayerCount, nullptr);
            std::vector<VkLayerProperties> tVKAvailableLayers(uLayerCount); // TODO: Here we are allocating and deallocating +10400B (520 (VkLayerProperties size) * 20 (uLayerCount)) in the heap. It's not much and it's only one time, but it's a good practice to try to manage this memory on the stack to avoid memory fragmentation. See https://austinmorlan.com/posts/temporary_memory_allocator/
            vkEnumerateInstanceLayerProperties(&uLayerCount, tVKAvailableLayers.data());

            for (const char* sLayerName : Arcadia::VKGlobal::g_tValidationLayers)
            {
                bool bLayerFound = false;

                for (const VkLayerProperties& oVKLayerProperties : tVKAvailableLayers)
                {
                    if (strcmp(sLayerName, oVKLayerProperties.layerName) == 0)
                    {
                        bLayerFound = true;
                        break;
                    }
                }

                if (!bLayerFound)
                {
                    return false;
                }
            }

            return true;
        }

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

        VkImageView CreateImageView(const VkImage& _oImage, const VkFormat& _oFormat, const VkImageAspectFlags& _oAspectFlags, const uint32_t _uMipLevels)
        {
            VkImageViewCreateInfo oViewInfo{};
            oViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            oViewInfo.image = _oImage;
            oViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            oViewInfo.format = _oFormat;
            // Default mapping
            oViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            oViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            oViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            oViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            // The subresourceRange field describes what the image's purpose is and which part of the image should be accessed.
            oViewInfo.subresourceRange.aspectMask = _oAspectFlags;
            oViewInfo.subresourceRange.baseMipLevel = 0;
            oViewInfo.subresourceRange.levelCount = _uMipLevels;
            oViewInfo.subresourceRange.baseArrayLayer = 0;
            oViewInfo.subresourceRange.layerCount = 1;

            VkImageView oImageView;
            ARC_VK_CHECK(vkCreateImageView(Arcadia::VK::CVK_LogicalDevice::GetVKDevice(), &oViewInfo, nullptr, &oImageView), "Failed to create image view!");

            return oImageView;
        }

        std::string GetVersionString(uint32_t _uVersion)
        {
            char str[64];
            sprintf_s(str, "%d.%d.%d", VK_VERSION_MAJOR(_uVersion), VK_VERSION_MINOR(_uVersion), VK_VERSION_PATCH(_uVersion));
            return std::string(str);
        }

        /** @} */ // end of VK_Utils group
    }
}