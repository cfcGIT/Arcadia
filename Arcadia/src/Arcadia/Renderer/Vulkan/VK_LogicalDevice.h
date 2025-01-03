#pragma once

namespace Arcadia
{
    namespace VK
    {
        class CVK_PhysicalDevice;

        class CVK_LogicalDevice
        {
        public:
            CVK_LogicalDevice(const CVK_PhysicalDevice& _oPhysicalDevice);
            ~CVK_LogicalDevice();

            static CVK_LogicalDevice* Create(const CVK_PhysicalDevice& _oPhysicalDevice);
            inline VkDevice GetVulkanDevice() { return m_oVKDevice; }

        private:
            VkDevice m_oVKDevice = VK_NULL_HANDLE;

            VkQueue m_oVKGraphicsQueue = VK_NULL_HANDLE;
            //VkQueue m_oVKPresentQueue = VK_NULL_HANDLE;
            VkQueue m_oVKTransferQueue = VK_NULL_HANDLE;
        };
    }
}