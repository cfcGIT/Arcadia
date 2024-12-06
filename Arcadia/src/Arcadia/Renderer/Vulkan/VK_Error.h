#pragma once

#include "vulkan/vulkan.h"

namespace Arcadia
{
    namespace VK
    {
        VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT _messageTypes,
            const VkDebugUtilsMessengerCallbackDataEXT* _pCallbackData,
            void* pUserData_);

        const char* GetVKResultString(VkResult _oVKResult);
        void _CheckVKResult(const char* _sFile, int _iLine, VkResult _oVKResult, const char* _sErrorMessage);
    }
}