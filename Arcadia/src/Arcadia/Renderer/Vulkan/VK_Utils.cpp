#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

#include "Arcadia/Renderer/Vulkan/VK_Context.h"

#include "GLFW/glfw3.h"

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
        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& oCreateInfo_)
        {
            oCreateInfo_ = {};
            oCreateInfo_.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            oCreateInfo_.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            oCreateInfo_.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            oCreateInfo_.pfnUserCallback = Arcadia::VK::DebugCallback;
            oCreateInfo_.pUserData = nullptr; // Optional
        }

        /**
        * @brief Check that all of the validation layers exist in the available layers list
        */
        bool CheckValidationLayerSupport()
        {
            uint32_t uLayerCount;
            vkEnumerateInstanceLayerProperties(&uLayerCount, nullptr);

            std::vector<VkLayerProperties> tAvailableLayers(uLayerCount);
            vkEnumerateInstanceLayerProperties(&uLayerCount, tAvailableLayers.data());

            for (const char* sLayerName : Arcadia::VK::s_tValidationLayers)
            {
                bool bLayerFound = false;

                for (const VkLayerProperties& oLayerProperties : tAvailableLayers)
                {
                    if (strcmp(sLayerName, oLayerProperties.layerName) == 0)
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

        /** @} */ // end of VK_Utils group
    }
}