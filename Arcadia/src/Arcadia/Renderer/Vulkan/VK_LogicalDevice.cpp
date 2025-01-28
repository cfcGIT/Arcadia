#include "Arcadia/Renderer/Vulkan/VK_LogicalDevice.h"

#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_PhysicalDevice.h"

namespace Arcadia
{
    namespace VK
    {
        CVK_LogicalDevice::CVK_LogicalDevice(const CVK_PhysicalDevice& _oPhysicalDevice)
        {
            CVK_PhysicalDevice::SQueueFamilyIndices oIndices = _oPhysicalDevice.GetQueueFamilies();

            std::vector<VkDeviceQueueCreateInfo> tQueueCreateInfos;
            std::set<uint32_t> tUniqueQueueFamilies = { oIndices.uGraphicsFamily.value(), /*oIndices.uPresentFamily.value() ,*/ oIndices.uTransferFamily.value()};
            float queuePriority = 1.0f;
            for (uint32_t uQueueFamily : tUniqueQueueFamilies)
            {
                VkDeviceQueueCreateInfo oQueueCreateInfo{}; // This structure describes the number of queues we want for a single queue family. Right now we're only interested in a queue with graphics capabilities
                oQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                oQueueCreateInfo.queueFamilyIndex = uQueueFamily;
                oQueueCreateInfo.queueCount = 1;
                oQueueCreateInfo.pQueuePriorities = &queuePriority; // Vulkan lets you assign priorities to queues to influence the scheduling of command buffer execution using floating point numbers between 0.0 and 1.0.This is required even if there is only a single queue
                tQueueCreateInfos.push_back(oQueueCreateInfo);
            }

            VkPhysicalDeviceFeatures deviceFeatures{};
            deviceFeatures.samplerAnisotropy = VK_TRUE;
            deviceFeatures.sampleRateShading = VK_TRUE; // enable sample shading feature for the device

            VkDeviceCreateInfo oCreateInfo{};
            oCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            oCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(tQueueCreateInfos.size());
            oCreateInfo.pQueueCreateInfos = tQueueCreateInfos.data();

            oCreateInfo.pEnabledFeatures = &deviceFeatures;

            // Extensions
            oCreateInfo.enabledExtensionCount = static_cast<uint32_t>(Arcadia::VKGlobal::g_tDeviceExtensions.size());
            oCreateInfo.ppEnabledExtensionNames = Arcadia::VKGlobal::g_tDeviceExtensions.data();

            // Validation layers
            if (Arcadia::VKGlobal::g_bVKDebug)
            {
                oCreateInfo.enabledLayerCount = static_cast<uint32_t>(Arcadia::VKGlobal::g_tValidationLayers.size());
                oCreateInfo.ppEnabledLayerNames = Arcadia::VKGlobal::g_tValidationLayers.data();
            }
            else
            {
                oCreateInfo.enabledLayerCount = 0;
            }

            // Instantiate the logical device
            ARC_VK_CHECK(vkCreateDevice(Arcadia::VK::CVK_PhysicalDevice::GetVKPhysicalDevice(), &oCreateInfo, nullptr, &m_oVKDevice), "Failed to create logical device!");

            // We can use the vkGetDeviceQueue function to retrieve queue handles for each queue family
            vkGetDeviceQueue(m_oVKDevice, oIndices.uGraphicsFamily.value(), 0, &m_oVKGraphicsQueue);
            //vkGetDeviceQueue(m_oVKDevice, oIndices.uPresentFamily.value(), 0, &m_oVKPresentQueue);
            vkGetDeviceQueue(m_oVKDevice, oIndices.uTransferFamily.value(), 0, &m_oVKTransferQueue);
        }

        CVK_LogicalDevice::~CVK_LogicalDevice()
        {
            vkDestroyDevice(m_oVKDevice, nullptr);
            m_oVKDevice = VK_NULL_HANDLE;
        }

        /**
        * @brief Create the logical device
        */
        CVK_LogicalDevice* CVK_LogicalDevice::Create(const CVK_PhysicalDevice& _oPhysicalDevice)
        {
            return arcnew CVK_LogicalDevice(_oPhysicalDevice);
        }
    }
}