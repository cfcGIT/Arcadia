#include "Arcadia/Renderer/RendererAPI.h"

// TODO: include if vulkan
#include "Arcadia/Renderer/Vulkan/VK_Shader.h"
#include "Shader.h"

namespace Arcadia
{
    CShader* CShader::Create(const char* _sShaderPath)
    {
        switch (Arcadia::CRendererAPI::GetAPI())
        {
        case CRendererAPI::EAPI::Vulkan:
            return arcnew Arcadia::VK::CVK_Shader(_sShaderPath);
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
        return nullptr;
    }
}
