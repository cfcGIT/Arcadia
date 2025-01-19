#include "Arcadia/Renderer/Renderer.h"

namespace Arcadia
{
    void CRenderer::Init()
    {
        m_pRendererAPI = CRendererAPI::Create();
        m_pRendererAPI->Init();
    }

    void CRenderer::Shutdown()
    {
        m_pRendererAPI->Shutdown();
        delete m_pRendererAPI;
        m_pRendererAPI = nullptr;
    }
}