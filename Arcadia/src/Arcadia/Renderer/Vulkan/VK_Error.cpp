#include "Arcadia/Renderer/Vulkan/VK_Error.h"

#define ARC_VK_ERROR_STRING(x) case x: return #x

namespace Arcadia
{
    namespace VK
    {
        // For doxygen doc
        /** @defgroup VKErrorGroup VK_Error
        *  VK_Error group
        *  @{
        */

        /**
        * @brief Callback for the vulkan validation layers
        * 
        * Display WARN if _messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT (important enough to show)
        * 
        * See [PFN_vkDebugUtilsMessengerCallbackEXT doc](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/PFN_vkDebugUtilsMessengerCallbackEXT.html)
        */
        VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT _messageTypes,
            const VkDebugUtilsMessengerCallbackDataEXT* _pCallbackData,
            void* pUserData_)
        {
            // Message is important enough to show
            if (_messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            {
                ARC_VK_WARN("Validation layer: {0}", _pCallbackData->pMessage);
            }

            return VK_FALSE;
        }

        /**
        * @brief Get string of VkResult
        * 
        * Based on [nvpro_core](https://github.com/nvpro-samples/nvpro_core/blob/master/nvvk/error_vk.cpp) and [vkDOOM3](https://github.com/DustinHLand/vkDOOM3/blob/master/neo/renderer/Vulkan/RenderBackend_VK.cpp)
        */
        const char* GetVKResultString(VkResult _oVKResult)
        {
            switch (_oVKResult)
            {
                ARC_VK_ERROR_STRING(VK_SUCCESS);
                ARC_VK_ERROR_STRING(VK_NOT_READY);
                ARC_VK_ERROR_STRING(VK_TIMEOUT);
                ARC_VK_ERROR_STRING(VK_EVENT_SET);
                ARC_VK_ERROR_STRING(VK_EVENT_RESET);
                ARC_VK_ERROR_STRING(VK_INCOMPLETE);
                ARC_VK_ERROR_STRING(VK_ERROR_OUT_OF_HOST_MEMORY);
                ARC_VK_ERROR_STRING(VK_ERROR_OUT_OF_DEVICE_MEMORY);
                ARC_VK_ERROR_STRING(VK_ERROR_INITIALIZATION_FAILED);
                ARC_VK_ERROR_STRING(VK_ERROR_DEVICE_LOST);
                ARC_VK_ERROR_STRING(VK_ERROR_MEMORY_MAP_FAILED);
                ARC_VK_ERROR_STRING(VK_ERROR_LAYER_NOT_PRESENT);
                ARC_VK_ERROR_STRING(VK_ERROR_EXTENSION_NOT_PRESENT);
                ARC_VK_ERROR_STRING(VK_ERROR_FEATURE_NOT_PRESENT);
                ARC_VK_ERROR_STRING(VK_ERROR_INCOMPATIBLE_DRIVER);
                ARC_VK_ERROR_STRING(VK_ERROR_TOO_MANY_OBJECTS);
                ARC_VK_ERROR_STRING(VK_ERROR_FORMAT_NOT_SUPPORTED);
                ARC_VK_ERROR_STRING(VK_ERROR_FRAGMENTED_POOL);
                ARC_VK_ERROR_STRING(VK_ERROR_OUT_OF_POOL_MEMORY);
                ARC_VK_ERROR_STRING(VK_ERROR_INVALID_EXTERNAL_HANDLE);
                ARC_VK_ERROR_STRING(VK_ERROR_SURFACE_LOST_KHR);
                ARC_VK_ERROR_STRING(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
                ARC_VK_ERROR_STRING(VK_SUBOPTIMAL_KHR);
                ARC_VK_ERROR_STRING(VK_ERROR_OUT_OF_DATE_KHR);
                ARC_VK_ERROR_STRING(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
                ARC_VK_ERROR_STRING(VK_ERROR_VALIDATION_FAILED_EXT);
                ARC_VK_ERROR_STRING(VK_ERROR_INVALID_SHADER_NV);
                ARC_VK_ERROR_STRING(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
                ARC_VK_ERROR_STRING(VK_ERROR_FRAGMENTATION_EXT);
                ARC_VK_ERROR_STRING(VK_ERROR_NOT_PERMITTED_EXT);
                ARC_VK_ERROR_STRING(VK_ERROR_INVALID_DEVICE_ADDRESS_EXT);
                ARC_VK_ERROR_STRING(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
                default: return "unknown";
            };
        }

        /**
        * @brief Check VkResult:
        * * Nothing if VK_SUCCESS
        * * WARN if > VK_SUCCESS
        * * ASSERT if < VK_SUCCESS
        * 
        * Called from MACRO ARC_VK_CHECK, e.g.: ARC_VK_CHECK(oRes, "Failed to create instance!");
        * 
        * @param _sFile: File where it comes (`__FILE__`)
        * @param _iLine: Line of the _sFile where it comes (`__LINE__`)
        * @param _oVKResult: VkResult to check
        * @param _sErrorMessage: WARN/ASSERT message to display if not VK_SUCCESS
        */
        void _CheckVKResult(const char* _sFile, int _iLine, VkResult _oVKResult, const char* _sErrorMessage)
        {
            if (_oVKResult == VK_SUCCESS)
            {
                return;
            }
            else if (_oVKResult > VK_SUCCESS)
            {
                ARC_VK_WARN("{0}({1}): {2} ({3})", _sFile, _iLine, _sErrorMessage, GetVKResultString(_oVKResult));
            }

            ARC_VK_ASSERT(_oVKResult >= VK_SUCCESS, "{0}({1}): {2} ({3})", _sFile, _iLine, _sErrorMessage, GetVKResultString(_oVKResult));
        }


        /** @} */ // end of VK_Error group
    }
}
