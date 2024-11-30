#pragma once

#include "vulkan/vulkan.h"

namespace Arcadia::VK
{

    VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT _messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT _messageTypes,
        const VkDebugUtilsMessengerCallbackDataEXT* _pCallbackData,
        void* pUserData_);

    const char* GetResultString(VkResult _result);
    void CheckResult(VkResult _result, const char* _sErrorMessage, const char* _sFile, int _iLine);
}