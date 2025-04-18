#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_LogicalDevice.h"

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

        std::string GetVersionString(uint32_t _uVersion)
        {
            char str[64];
            sprintf_s(str, "%d.%d.%d", VK_VERSION_MAJOR(_uVersion), VK_VERSION_MINOR(_uVersion), VK_VERSION_PATCH(_uVersion));
            return std::string(str);
        }

        /** @} */ // end of VK_Utils group
    }
}