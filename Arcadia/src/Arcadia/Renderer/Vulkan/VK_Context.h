#pragma once

#include "Arcadia/Renderer/Renderer.h"
#include "Arcadia/Renderer/RenderContext.h"

namespace Arcadia
{
    namespace VK
    {
        class CVK_LogicalDevice;
        class CVK_PhysicalDevice;

        class CVK_Context : public CRenderContext
        {
        public:
            CVK_Context();
            ~CVK_Context();

            virtual void Init() override;
            virtual void InitGUI() override;
            virtual void Destroy() override;

            inline CVK_LogicalDevice* GetDevice() const { return m_pLogicalDevice; }
            inline CVK_PhysicalDevice* GetPhysicalDevice() const { return m_pPhysicalDevice; }

            inline static VkInstance GetVKInstance() { return m_oVKInstance; }

        private:
            VkResult CreateInstance();

            VkResult SetupDebugMessenger();
            void CleanupDebugMessenger();

        private:
            inline static VkInstance m_oVKInstance = VK_NULL_HANDLE;
            VkDebugUtilsMessengerEXT m_oDebugMessenger = VK_NULL_HANDLE;

            // Devices refs
            CVK_PhysicalDevice* m_pPhysicalDevice = nullptr;
            CVK_LogicalDevice* m_pLogicalDevice = nullptr;
        };
    }
}