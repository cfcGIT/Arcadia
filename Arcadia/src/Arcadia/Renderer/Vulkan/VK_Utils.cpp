#include "Arcadia/Renderer/Vulkan/VK_Utils.h"
#include "Arcadia/Renderer/Vulkan/VK_Error.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    namespace VK
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
        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& oCreateInfo_)
        {
            oCreateInfo_ = {};
            oCreateInfo_.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            oCreateInfo_.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            oCreateInfo_.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            oCreateInfo_.pfnUserCallback = Arcadia::VK::DebugCallback;
            oCreateInfo_.pUserData = nullptr; // Optional
        }

        /** @} */ // end of VK_Utils group
    }
}