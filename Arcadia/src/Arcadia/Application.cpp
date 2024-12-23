#include "Arcadia/Application.h"

#include "Arcadia/Events/MouseEvent.h"
#include "Arcadia/Renderer/Renderer.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    CApplication* CApplication::m_oApplication = nullptr;

    CApplication::CApplication()
    {
        m_oApplication = this;

        m_pWindow = std::make_unique<CWindow>();
        m_pWindow->SetEventCallback([this](CEvent& _oEvent) { OnEvent(_oEvent); });

        CRenderer::Init();
    }

    CApplication::~CApplication()
    {
        CRenderer::Shutdown();
    }

    void CApplication::OnEvent(CEvent& _oEvent)
    {
        // Dispatch: if WindowCloseEvent -> OnWindowClose
        CEventDispatcher oDispatcher(_oEvent);
        oDispatcher.Dispatch<CWindowCloseEvent>([this](CWindowCloseEvent& _oEvent) -> bool { return OnWindowClose(_oEvent); });

        // Iterate m_LayerStack backwards: from the end (overlays) to the beginning (layers)
        // E.g.: ImGui will be Overlay, app and editor will be Layers. We want to capture ImGui events over other layer events.
        for (auto it = m_oLayerStack.rbegin(); it != m_oLayerStack.rend(); ++it)
        {
            // If overlay handled the event -> break, layers will not get it
            if (_oEvent.IsHandled())
            {
                break;
            }
            (*it)->OnEvent(_oEvent);
        }
    }

    void CApplication::Run()
    {
        while (m_bRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (CLayer* pLayer : m_oLayerStack)
            {
                pLayer->OnUpdate();
            }

            m_pWindow->OnUpdate();
        }
    }

    void CApplication::PushLayer(CLayer* _pLayer)
    {
        m_oLayerStack.PushLayer(_pLayer);
    }

    void CApplication::PushOverlay(CLayer* _pOverlay)
    {
        m_oLayerStack.PushOverlay(_pOverlay);
    }

    bool CApplication::OnWindowClose(CWindowCloseEvent& _oEvent)
    {
        m_bRunning = false;
        return true;
    }
}
