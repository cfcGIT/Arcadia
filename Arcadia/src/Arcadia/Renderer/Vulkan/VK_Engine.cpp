#include "Arcadia/Renderer/Vulkan/VK_Engine.h"
#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

namespace Arcadia::VK
{

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

        std::vector<const char*> extensions = Arcadia::VK::GetRequiredExtensions(bVKDebug);
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        // Include the validation layer names if they are enabled
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if (bVKDebug)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(vValidationLayers.size());
            createInfo.ppEnabledLayerNames = vValidationLayers.data();

            Arcadia::VK::PopulateDebugMessengerCreateInfo(debugCreateInfo);
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