#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_LogicalDevice.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace Arcadia
{
    namespace VK
    {
        /**
        * @brief Create a image view from an image
        */
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
    }
}