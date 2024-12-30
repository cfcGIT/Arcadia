#pragma once

namespace Arcadia
{
    namespace VK
    {
        class CVK_PhysicalDevice
        {
        public:
            struct SQueueFamilyIndices
            {
                std::optional<uint32_t> uGraphicsFamily;
                //std::optional<uint32_t> uPresentFamily;
                std::optional<uint32_t> uTransferFamily;

                bool IsComplete()
                {
                    return uGraphicsFamily.has_value() && /*uPresentFamily.has_value() && */uTransferFamily.has_value();
                }
            };
        public:
            CVK_PhysicalDevice();
            ~CVK_PhysicalDevice();

            static CVK_PhysicalDevice* Select();
            inline VkPhysicalDevice GetVulkanPhysicalDevice() const { return m_oPhysicalDevice; }

            inline VkPhysicalDeviceProperties GetProperties() const { return m_oProperties; }
            inline VkPhysicalDeviceFeatures GetFeatures() const { return m_oFeatures; }

            inline SQueueFamilyIndices GetQueueFamilies() const { return m_oQueueFamilyIndices; }


            int RateDeviceSuitability(const VkPhysicalDevice& _oPhysicalDevice);
            SQueueFamilyIndices FindQueueFamilies() const;

            // Physical device info
            std::string GetVendorName();
            std::string GetDeviceType();
            void PrintsPhysicalDeviceProperties();


        private:
            VkPhysicalDevice m_oPhysicalDevice = VK_NULL_HANDLE; // TODO: We can pick and use multiple physical devices
            VkPhysicalDeviceProperties m_oProperties;
            VkPhysicalDeviceFeatures m_oFeatures;

            SQueueFamilyIndices m_oQueueFamilyIndices;
        };
    }
}