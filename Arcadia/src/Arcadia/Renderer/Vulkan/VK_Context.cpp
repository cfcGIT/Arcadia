#include "Arcadia/Renderer/Vulkan/VK_Context.h"

#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

namespace Arcadia
{
    namespace VK
    {

        CVK_Context::CVK_Context()
        {
        }

        CVK_Context::~CVK_Context()
        {
        }

        void CVK_Context::Init()
        {       
            // Create instance
            ARC_VK_CHECK(CreateInstance(), "Failed to create vulkan instance!");
            ARC_VK_INFO("Vulkan instance created!");

            // TODO: Select physical device
            // ...
        
            // TODO: Create logical device
            // ...
        }

        void CVK_Context::InitGUI()
        {

        }

        VkResult CVK_Context::CreateInstance()
        {
            if (s_bVKDebug && !Arcadia::VKUtils::CheckValidationLayerSupport())
            {
                ARC_VK_ASSERT(false, "Validation layers requested, but not available!");
            }

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

            // TODO: add something to add extension. For example to enable ray tracing we need to add some others extensions
            std::vector<const char*> tExtensions = Arcadia::VKUtils::GetRequiredExtensions(s_bVKDebug);
            oCreateInfo.enabledExtensionCount = static_cast<uint32_t>(tExtensions.size());
            oCreateInfo.ppEnabledExtensionNames = tExtensions.data();

            // Include the validation layer names if they are enabled
            VkDebugUtilsMessengerCreateInfoEXT oDebugCreateInfo{};
            if (s_bVKDebug)
            {
                oCreateInfo.enabledLayerCount = static_cast<uint32_t>(s_tValidationLayers.size());
                oCreateInfo.ppEnabledLayerNames = s_tValidationLayers.data();

                Arcadia::VKUtils::PopulateDebugMessengerCreateInfo(oDebugCreateInfo);
                oCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&oDebugCreateInfo;
            }
            else
            {
                oCreateInfo.enabledLayerCount = 0;
                oCreateInfo.pNext = nullptr;
            }

            return vkCreateInstance(&oCreateInfo, nullptr, &m_oVKInstance);
        }
    }
}