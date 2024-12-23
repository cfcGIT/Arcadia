#pragma once

#include "Arcadia/Renderer/Renderer.h"
#include "Arcadia/Renderer/RenderContext.h"

#include "vulkan/vulkan.h"

namespace Arcadia
{
    namespace VK
    {
        static const std::vector<const char*> s_tValidationLayers = {
                "VK_LAYER_KHRONOS_validation"
        };

        class CVK_Context : public CRenderContext
        {
        public:
            // TODO: CVar
            static const bool s_bVKDebug =
    #ifdef ARC_VK_DEBUG
                true;
    #else
                false;
    #endif

        public:
            CVK_Context();
            ~CVK_Context();

            virtual void Init() override;

            virtual void InitGUI() override;

            inline VkInstance GetInstance() const { return m_oVKInstance; }

            inline static CVK_Context* Get() { return (CVK_Context*)CRenderer::GetContext(); }

        private:
            // Create vulkan instance
            VkResult CreateInstance();

        private:
            VkInstance m_oVKInstance = VK_NULL_HANDLE;
        };
    }
}