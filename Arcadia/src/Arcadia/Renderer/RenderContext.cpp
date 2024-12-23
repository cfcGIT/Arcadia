#include "Arcadia/Renderer/RenderContext.h"

#include "Arcadia/Renderer/Renderer.h"
#include "Arcadia/Renderer/Vulkan/VK_Context.h"

namespace Arcadia
{
    CRenderContext* CRenderContext::Create()
    {
        CRendererAPI::EAPI oAPI = CRenderer::GetAPI();
        switch (oAPI)
        {
            case CRendererAPI::EAPI::Vulkan:
                return new Arcadia::VK::CVK_Context();
            case CRendererAPI::EAPI::OpenGL:
                ARC_CORE_ASSERT(false, "RendererAPI::OpenGL is currently not supported!");
                return nullptr;
            case CRendererAPI::EAPI::DX12:
                ARC_CORE_ASSERT(false, "RendererAPI::DX12 is currently not supported!");
                return nullptr;
            default:
                ARC_CORE_ASSERT(false, "Unknown RendererAPI!");
                return nullptr;
        }
    }
}
