#include "Arcadia/Renderer/Vulkan/VK_PhysicalDevice.h"

#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"
#include "Arcadia/Renderer/Vulkan/VK_Utils.h"

namespace Arcadia
{
    namespace VK
    {
        CVK_PhysicalDevice::CVK_PhysicalDevice()
        {
            uint32_t uDeviceCount = 0;
            vkEnumeratePhysicalDevices(Arcadia::VK::CVK_Context::GetVKInstance(), &uDeviceCount, nullptr);
            ARC_VK_ASSERT(uDeviceCount > 0, "Failed to find GPUs with Vulkan support!");

            std::vector<VkPhysicalDevice> tDevices(uDeviceCount);
            vkEnumeratePhysicalDevices(Arcadia::VK::CVK_Context::GetVKInstance(), &uDeviceCount, tDevices.data());

            // Pick the first device that suits. TODO: Improve selection
            for (const VkPhysicalDevice& oVKPhysicalDevice : tDevices)
            {
                int iScore = RateDeviceSuitability(oVKPhysicalDevice);
                if (iScore > 0)
                {
                    m_oVKPhysicalDevice = oVKPhysicalDevice;
                    break;
                }
            }

            m_oQueueFamilyIndices = FindQueueFamilies();
        }

        CVK_PhysicalDevice::~CVK_PhysicalDevice()
        {
        }

        /**
        * @brief Select a physical device (GPU) that suits us
        */
        CVK_PhysicalDevice* CVK_PhysicalDevice::Select()
        {
            return arcnew CVK_PhysicalDevice();
        }

        /**
        * @brief Rate the suitability of the physical device assigning a score
        * 
        * @param _oVKPhysicalDevice Physical device to rate
        * @return Score assigned to _oVKPhysicalDevice
        */
        int CVK_PhysicalDevice::RateDeviceSuitability(const VkPhysicalDevice& _oVKPhysicalDevice)
        {
            int iScore = 0;

            vkGetPhysicalDeviceProperties(_oVKPhysicalDevice, &m_oVKProperties);
            vkGetPhysicalDeviceFeatures(_oVKPhysicalDevice, &m_oVKFeatures);

            // Discrete GPUs have a significant performance advantage
            if (m_oVKProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            {
                iScore += 1000;
            }

            // Maximum possible size of textures affects graphics quality
            iScore += m_oVKProperties.limits.maxImageDimension2D;

            // Application can't function without geometry shaders
            if (!m_oVKFeatures.geometryShader)
            {
                return 0;
            }

            return iScore;
        }

        /**
        * @brief Find the queue families of the physical device
        * 
        * @return Struct 'SQueueFamilyIndices' with the queue family indices
        */
        CVK_PhysicalDevice::SQueueFamilyIndices CVK_PhysicalDevice::FindQueueFamilies() const
        {
            SQueueFamilyIndices oIndices;

            // Logic to find queue family indices to populate struct with
            uint32_t uQueueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(m_oVKPhysicalDevice, &uQueueFamilyCount, nullptr);
            std::vector<VkQueueFamilyProperties> tQueueFamilies(uQueueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(m_oVKPhysicalDevice, &uQueueFamilyCount, tQueueFamilies.data());

            // TODO: Add check VK_QUEUE_COMPUTE_BIT for compute operations (e.g. https://vulkan-tutorial.com/Compute_Shader)
            for (uint32_t i = 0; i < uQueueFamilyCount; ++i)
            {
                if (tQueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                {
                    oIndices.uGraphicsFamily = i;
                    // TODO: Check back when I want to retrieve the presentation support for the device. https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Window_surface
                    //   Now we're creating the surface later in VK_SwampChain
# if 0
                    // Look for a queue family that has the capability of presenting to our window surface
                    VkBool32 bPresentSupport = false;
                    vkGetPhysicalDeviceSurfaceSupportKHR(m_oVKPhysicalDevice, i, CVK_Surface::Get().GetVulkanSurface(), &bPresentSupport);
                    if (bPresentSupport)
                    {
                        oIndices.uPresentFamily = i;
                    }
#endif
                }
                else if (tQueueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) // with the VK_QUEUE_TRANSFER_BIT bit, but not the VK_QUEUE_GRAPHICS_BIT
                {
                    oIndices.uTransferFamily = i;
                }

                if (oIndices.IsComplete())
                {
                    break;
                }
            }

            return oIndices;
        }

        // Physical device info
        /**
        * @brief Get the vendor name of the physical device (AMD, NVIDIA, ...)
        */
        std::string CVK_PhysicalDevice::GetVendorName()
        {
            switch (m_oVKProperties.vendorID)
            {
                case 0x1002: return ("AMD");
                case 0x1010: return ("ImgTec");
                case 0x10DE: return ("NVIDIA");
                case 0x13B5: return ("ARM");
                case 0x5143: return ("Qualcomm");
                case 0x8086: return ("INTEL");
            }
            return ("Unknown Vendor");
        }

        /**
        * @brief Get the device type of the physical device (Integrated, Discrete, ...)
        */
        std::string CVK_PhysicalDevice::GetDeviceType()
        {
            switch (m_oVKProperties.deviceType)
            {
                case VK_PHYSICAL_DEVICE_TYPE_OTHER: return ("Other");
                case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return ("Integrated GPU");
                case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return ("Discrete GPU");
                case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return ("Virtual GPU");
                case VK_PHYSICAL_DEVICE_TYPE_CPU: return ("CPU");
                default: return ("Unknown Device Type");
            }
        }

        /**
        * @brief Prints information on some physical device properties
        */
        void CVK_PhysicalDevice::PrintsPhysicalDeviceProperties()
        {
            ARC_VK_INFO(" - Device Name    : {0}", m_oVKProperties.deviceName);
            ARC_VK_INFO(" - Vendor         : {0}", GetVendorName().c_str());
            ARC_VK_INFO(" - Driver Version : {0}", Arcadia::VKUtils::GetVersionString(m_oVKProperties.driverVersion).c_str());
            ARC_VK_INFO(" - API Version    : {0}", Arcadia::VKUtils::GetVersionString(m_oVKProperties.apiVersion).c_str());
            ARC_VK_INFO(" - Device Type    : {0}", GetDeviceType().c_str());
        }
    }
}