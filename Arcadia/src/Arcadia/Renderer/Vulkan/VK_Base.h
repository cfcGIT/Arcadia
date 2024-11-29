#pragma once

#include "Arcadia/Log.h"
#include "GLFW/glfw3.h"

#include "vulkan/vulkan.h"

/**
* 
*/

namespace Arcadia
{
    namespace VK
    {
        const bool bVKDebug =
#ifdef ARC_VK_DEBUG
            true;
#else
            false;
#endif
        const std::vector<const char*> vValidationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        namespace Utils
        {
            // From https://github.com/nvpro-samples/nvpro_core/blob/master/nvvk/error_vk.cpp
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

            VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT _messageType,
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
        }

        // E.g.: Arcadia::VK::CheckResult(res, "Failed to create instance!", __FILE__, __LINE__);
        void CheckResult(VkResult _result, const char* _sErrorMessage, const char* _sFile, int _iLine)
        {
            if (_result == VK_SUCCESS)
            {
                return;
            }
            else if (_result > 0)
            {
                ARC_VK_WARN("{0}({1}): {2} ({3})", _sFile, _iLine, _sErrorMessage, Utils::GetResultString(_result));
            }

            ARC_VK_ASSERT(_result >= 0, "{0}({1}): {2} ({3})", _sFile, _iLine, _sErrorMessage, Utils::GetResultString(_result));
        }

        // Will return the required list of extensions based on whether validation layers are enabled or not
        std::vector<const char*> GetRequiredExtensions()
        {
            uint32_t uGlfwExtensionCount = 0;
            const char** pGlfwExtensions;
            pGlfwExtensions = glfwGetRequiredInstanceExtensions(&uGlfwExtensionCount);

            std::vector<const char*> vExtensions(pGlfwExtensions, pGlfwExtensions + uGlfwExtensionCount);

            return vExtensions;
        }

        // TODO: Separate this function from anothers. Create VK_Utils class?
        void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo_)
        {
            createInfo_ = {};
            createInfo_.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            createInfo_.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            createInfo_.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            createInfo_.pfnUserCallback = Utils::DebugCallback;
            createInfo_.pUserData = nullptr; // Optional
        }

        // Create vulkan instance
        VkResult CreateInstance(VkInstance& instance_)
        {
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Sandbox";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "Arcadia";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            std::vector<const char*> extensions = Arcadia::VK::GetRequiredExtensions();
            createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
            createInfo.ppEnabledExtensionNames = extensions.data();

            // Include the validation layer names if they are enabled
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
            if (bVKDebug)
            {
                createInfo.enabledLayerCount = static_cast<uint32_t>(vValidationLayers.size());
                createInfo.ppEnabledLayerNames = vValidationLayers.data();

                PopulateDebugMessengerCreateInfo(debugCreateInfo);
                createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
            }
            else
            {
                createInfo.enabledLayerCount = 0;
                createInfo.pNext = nullptr;
            }

            return vkCreateInstance(&createInfo, nullptr, &instance_);
        }
    }
}