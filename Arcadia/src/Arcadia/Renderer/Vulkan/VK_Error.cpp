#include "Arcadia/Renderer/Vulkan/VK_Error.h"
#include "Arcadia/Log.h"

namespace Arcadia::VK
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
    * From [nvpro_core](https://github.com/nvpro-samples/nvpro_core/blob/master/nvvk/error_vk.cpp))
    */
    const char* GetResultString(VkResult _result)
    {
        const char* sResultString = "unknown";

#define STR(a)            \
        case a:                   \
            sResultString = #a;   \
            break;

        switch (_result)
        {
            STR(VK_SUCCESS);
            STR(VK_NOT_READY);
            STR(VK_TIMEOUT);
            STR(VK_EVENT_SET);
            STR(VK_EVENT_RESET);
            STR(VK_INCOMPLETE);
            STR(VK_ERROR_OUT_OF_HOST_MEMORY);
            STR(VK_ERROR_OUT_OF_DEVICE_MEMORY);
            STR(VK_ERROR_INITIALIZATION_FAILED);
            STR(VK_ERROR_DEVICE_LOST);
            STR(VK_ERROR_MEMORY_MAP_FAILED);
            STR(VK_ERROR_LAYER_NOT_PRESENT);
            STR(VK_ERROR_EXTENSION_NOT_PRESENT);
            STR(VK_ERROR_FEATURE_NOT_PRESENT);
            STR(VK_ERROR_INCOMPATIBLE_DRIVER);
            STR(VK_ERROR_TOO_MANY_OBJECTS);
            STR(VK_ERROR_FORMAT_NOT_SUPPORTED);
            STR(VK_ERROR_FRAGMENTED_POOL);
            STR(VK_ERROR_OUT_OF_POOL_MEMORY);
            STR(VK_ERROR_INVALID_EXTERNAL_HANDLE);
            STR(VK_ERROR_SURFACE_LOST_KHR);
            STR(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
            STR(VK_SUBOPTIMAL_KHR);
            STR(VK_ERROR_OUT_OF_DATE_KHR);
            STR(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
            STR(VK_ERROR_VALIDATION_FAILED_EXT);
            STR(VK_ERROR_INVALID_SHADER_NV);
            STR(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT);
            STR(VK_ERROR_FRAGMENTATION_EXT);
            STR(VK_ERROR_NOT_PERMITTED_EXT);
            STR(VK_ERROR_INVALID_DEVICE_ADDRESS_EXT);
            STR(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT);
        }
#undef STR
        return sResultString;
    }

    /**
    * @brief Check VkResult:
    * * Nothing if VK_SUCCESS
    * * WARN if > VK_SUCCESS
    * * ASSERT if < VK_SUCCESS
    * 
    * E.g.: Arcadia::VK::CheckResult(res, "Failed to create instance!", `__FILE__`, `__LINE__`);
    * 
    * @param _result: VkResult to check
    * @param _sErrorMessage: WARN/ASSERT message to display if not VK_SUCCESS
    * @param _sFile: File where it comes (`__FILE__`)
    * @param _iLine: Line of the _sFile where it comes (`__LINE__`)
    */
    void CheckResult(VkResult _result, const char* _sErrorMessage, const char* _sFile, int _iLine)
    {
        if (_result == VK_SUCCESS)
        {
            return;
        }
        else if (_result > VK_SUCCESS)
        {
            ARC_VK_WARN("{0}({1}): {2} ({3})", _sFile, _iLine, _sErrorMessage, GetResultString(_result));
        }

        ARC_VK_ASSERT(_result >= VK_SUCCESS, "{0}({1}): {2} ({3})", _sFile, _iLine, _sErrorMessage, GetResultString(_result));
    }

    /** @} */ // end of VK_Error group
}