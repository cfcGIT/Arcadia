#include "Arcadia/Renderer/RenderCommand.h"

namespace Arcadia
{
    std::unique_ptr<CRendererAPI> CRenderCommand::m_oRendererAPI = CRendererAPI::Create();

    void CRenderCommand::Init()
    {
        m_oRendererAPI->Init();
    }
}