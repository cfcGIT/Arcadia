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
            inline VkPhysicalDevice GetVulkanPhysicalDevice() const { return m_oVKPhysicalDevice; }

            inline VkPhysicalDeviceProperties GetVKProperties() const { return m_oVKProperties; }
            inline VkPhysicalDeviceFeatures GetVKFeatures() const { return m_oVKFeatures; }

            inline SQueueFamilyIndices GetQueueFamilies() const { return m_oQueueFamilyIndices; }


            int RateDeviceSuitability(const VkPhysicalDevice& _oPhysicalDevice);
            SQueueFamilyIndices FindQueueFamilies() const;

            // Physical device info
            std::string GetVendorName();
            std::string GetDeviceType();
            void PrintsPhysicalDeviceProperties();


        private:
            VkPhysicalDevice m_oVKPhysicalDevice = VK_NULL_HANDLE; // TODO: We can pick and use multiple physical devices
            VkPhysicalDeviceProperties m_oVKProperties;
            VkPhysicalDeviceFeatures m_oVKFeatures;

            SQueueFamilyIndices m_oQueueFamilyIndices;
        };
    }
}