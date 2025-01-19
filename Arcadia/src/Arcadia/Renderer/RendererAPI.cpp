#include "Arcadia/Renderer/RendererAPI.h"
#include "Arcadia/Renderer/RenderContext.h"

// TODO: include if vulkan
#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"

namespace Arcadia
{
    CRendererAPI* CRendererAPI::Create()
    {
        switch (m_oAPI)
        {
            case CRendererAPI::EAPI::Vulkan:
                return arcnew Arcadia::VK::CVK_RendererAPI();
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
