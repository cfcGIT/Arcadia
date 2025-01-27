#pragma once

/**
* @brief Global VK vars
*/

namespace Arcadia
{
    namespace VKGlobal
    {
        static const std::vector<const char*> g_tValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        static const std::vector<const char*> g_tDeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        // TODO: CVar
        static const bool g_bVKDebug =
#ifdef ARC_VK_DEBUG
            true;
#else
            false;
#endif

        // Globals ptrs to VK objects
        inline const VkInstance* g_pVKInstance = nullptr;
        inline const VkDevice* g_pVKDevice = nullptr;
        inline const VkPhysicalDevice* g_pVKPhysicalDevice = nullptr;
        inline const VkSurfaceKHR* g_pVKSurface = nullptr;
    }
}