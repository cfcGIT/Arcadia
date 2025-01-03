#pragma once

#include "Arcadia/Renderer/RendererAPI.h"
#include "Arcadia/Renderer/Vulkan/VK_Context.h"

namespace Arcadia
{
    namespace VK
    {
        class CVK_RendererAPI : public CRendererAPI
        {
        public:
            virtual void Init() override;
            virtual void InitRenderContext() override;
            virtual void Shutdown() override;

        private:
            std::unique_ptr<CVK_Context> m_pContext = nullptr;
        };
    }
}