#include "Arcadia/Renderer/Vulkan/VK_Engine.h"
#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

namespace Arcadia
{
    namespace VK
    {
        // Create vulkan instance
        VkResult CreateInstance(VkInstance& oVkInstance_)
        {
            VkApplicationInfo oAppInfo{};
            oAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            oAppInfo.pApplicationName = "Sandbox";
            oAppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            oAppInfo.pEngineName = "Arcadia";
            oAppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            oAppInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo oCreateInfo{};
            oCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            oCreateInfo.pApplicationInfo = &oAppInfo;

            std::vector<const char*> tExtensions = Arcadia::VK::GetRequiredExtensions(bVKDebug);
            oCreateInfo.enabledExtensionCount = static_cast<uint32_t>(tExtensions.size());
            oCreateInfo.ppEnabledExtensionNames = tExtensions.data();

            // Include the validation layer names if they are enabled
            VkDebugUtilsMessengerCreateInfoEXT oDebugCreateInfo{};
            if (bVKDebug)
            {
                oCreateInfo.enabledLayerCount = static_cast<uint32_t>(tValidationLayers.size());
                oCreateInfo.ppEnabledLayerNames = tValidationLayers.data();

                Arcadia::VK::PopulateDebugMessengerCreateInfo(oDebugCreateInfo);
                oCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&oDebugCreateInfo;
            }
            else
            {
                oCreateInfo.enabledLayerCount = 0;
                oCreateInfo.pNext = nullptr;
            }

            return vkCreateInstance(&oCreateInfo, nullptr, &oVkInstance_);
        }
    }
}