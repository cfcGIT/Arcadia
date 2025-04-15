#pragma once

namespace Arcadia
{
    namespace VK
    {
        VkImageView CreateImageView(const VkImage& _oImage, const VkFormat& _oFormat, const VkImageAspectFlags& _oAspectFlags, const uint32_t _uMipLevels);
    }
}