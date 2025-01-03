#include "Arcadia/Renderer/Vulkan/VK_Context.h"

#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_LogicalDevice.h"
#include "Arcadia/Renderer/Vulkan/VK_PhysicalDevice.h"
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

        /**
        * @brief Init the VK context: create instance, devices, ...
        */
        void CVK_Context::Init()
        {
            // Create instance
            ARC_VK_CHECK(CreateInstance(), "Failed to create vulkan instance!");
            ARC_VK_INFO("Vulkan instance created!");

            // Setup debug messenger
            ARC_VK_CHECK(SetupDebugMessenger(), "Failed to setup debug messenger!");
            ARC_VK_INFO((Arcadia::VKGlobal::g_bVKDebug) ? "Debug messenger created!" : "Debug messenger not created because vkDebug is disabled!");

            // TODO: Create surface? Check back when I want to retrieve the presentation support for the device. https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Window_surface
            
            // Select physical device
            m_pPhysicalDevice = CVK_PhysicalDevice::Select();
            ARC_VK_ASSERT(m_pPhysicalDevice != VK_NULL_HANDLE, "Failed to find a suitable GPU!");
            ARC_VK_INFO("GPU found!");
            m_pPhysicalDevice->PrintsPhysicalDeviceProperties();

            // Create logical device
            m_pLogicalDevice = CVK_LogicalDevice::Create(*m_pPhysicalDevice);
            ARC_VK_INFO("Logical device created!");
        }

        void CVK_Context::InitGUI()
        {
        }

        void CVK_Context::Destroy()
        {
            // Destroy devices
            delete m_pLogicalDevice;
            delete m_pPhysicalDevice;

            // Destroy debug messenger
            CleanupDebugMessenger();

            // Destroy instance
            vkDestroyInstance(m_oVKInstance, nullptr);
            m_oVKInstance = nullptr;
        }

        /**
        * @brief Create the vulkan instance
        */
        VkResult CVK_Context::CreateInstance()
        {
            if (Arcadia::VKGlobal::g_bVKDebug && !Arcadia::VKUtils::CheckValidationLayerSupport())
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

            // TODO: add something to add extension. For example to enable ray tracing we need to add some others extensions (see https://youtu.be/tLwbj9qys18?t=1615)
            std::vector<const char*> tExtensions = Arcadia::VKUtils::GetRequiredExtensions(Arcadia::VKGlobal::g_bVKDebug);
            oCreateInfo.enabledExtensionCount = static_cast<uint32_t>(tExtensions.size());
            oCreateInfo.ppEnabledExtensionNames = tExtensions.data();

            // Include the validation layer names if they are enabled
            if (Arcadia::VKGlobal::g_bVKDebug)
            {
                oCreateInfo.enabledLayerCount = static_cast<uint32_t>(Arcadia::VKGlobal::g_tValidationLayers.size());
                oCreateInfo.ppEnabledLayerNames = Arcadia::VKGlobal::g_tValidationLayers.data();
            }
            else
            {
                oCreateInfo.enabledLayerCount = 0;
                oCreateInfo.pNext = nullptr;
            }

            return vkCreateInstance(&oCreateInfo, nullptr, &m_oVKInstance);
        }

        /**
        * @brief If debug is enabled, this function setups de debug mesenger
        */
        VkResult CVK_Context::SetupDebugMessenger()
        {
            if (!Arcadia::VKGlobal::g_bVKDebug) return VK_SUCCESS;

            VkDebugUtilsMessengerCreateInfoEXT oDebugCreateInfo{};
            Arcadia::VKUtils::PopulateDebugMessengerCreateInfo(oDebugCreateInfo);

            // Because this function is an extension function, it is not automatically loaded. We have to look up its address ourselves using vkGetInstanceProcAddr. We're going to create our own proxy function that handles this in the background
            PFN_vkCreateDebugUtilsMessengerEXT oVKCreateDebugUtilsMessengerEXTFunc = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_oVKInstance, "vkCreateDebugUtilsMessengerEXT");
            ARC_VK_ASSERT(oVKCreateDebugUtilsMessengerEXTFunc != NULL, "Failed to setup proxy debug messenger function!");

            return oVKCreateDebugUtilsMessengerEXTFunc(m_oVKInstance, &oDebugCreateInfo, nullptr, &m_oDebugMessenger);
        }

        /**
        * @brief Function to cleanup the debug messenger
        */
        void CVK_Context::CleanupDebugMessenger()
        {
            if (!Arcadia::VKGlobal::g_bVKDebug) return;
            PFN_vkDestroyDebugUtilsMessengerEXT oVkDestroyDebugUtilsMessengerEXTFunc = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_oVKInstance, "vkDestroyDebugUtilsMessengerEXT");
            if (oVkDestroyDebugUtilsMessengerEXTFunc != nullptr)
            {
                oVkDestroyDebugUtilsMessengerEXTFunc(m_oVKInstance, m_oDebugMessenger, nullptr);
            }
        }
    }
}