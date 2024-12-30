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
            inline VkDevice GetVulkanDevice() { return m_oDevice; }

        private:
            VkDevice m_oDevice = VK_NULL_HANDLE;

            VkQueue m_oGraphicsQueue = VK_NULL_HANDLE;
            //VkQueue m_oPresentQueue = VK_NULL_HANDLE;
            VkQueue m_oTransferQueue = VK_NULL_HANDLE;
        };
    }
}