#include "Arcadia/Renderer/Vulkan/VK_Utils.h"
#include "Arcadia/Renderer/Vulkan/VK_Error.h"

#include "GLFW/glfw3.h"

namespace Arcadia::VK
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
        pGlfwExtensions = glfwGetRequiredInstanceExtensions(&uGlfwExtensionCount);

        std::vector<const char*> vExtensions(pGlfwExtensions, pGlfwExtensions + uGlfwExtensionCount);

        if (_bValidationLayersEnabled)
        {
            vExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return vExtensions;
    }

    /**
    * @brief Create debug messenger to handle validation layers messages
    */
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo_)
    {
        createInfo_ = {};
        createInfo_.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo_.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo_.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo_.pfnUserCallback = Arcadia::VK::DebugCallback;
        createInfo_.pUserData = nullptr; // Optional
    }

    /** @} */ // end of VK_Utils group
}