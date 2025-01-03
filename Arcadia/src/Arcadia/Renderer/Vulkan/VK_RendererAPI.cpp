#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"

namespace Arcadia
{
    namespace VK
    {
        void CVK_RendererAPI::Init()
        {
            InitRenderContext();
            // TODO: Create swap chain, image views, render pass
            // ...
        }

        void CVK_RendererAPI::InitRenderContext()
        {
            m_pContext = std::make_unique<CVK_Context>();
            m_pContext->Init();
        }

        void CVK_RendererAPI::Shutdown()
        {
            m_pContext->Destroy();
        }
    }
}
