#include "Arcadia/Application.h"
#include "Arcadia/Events/MouseEvent.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    Application::Application()
    {
        m_puWindow = std::unique_ptr<Window>(Window::Create());
        m_puWindow->SetEventCallback([this](Event& _event) { OnEvent(_event); });
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& _event)
    {
        // Dispatch: if WindowCloseEvent -> OnWindowClose
        EventDispatcher dispatcher(_event);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& _event) -> bool { return OnWindowClose(_event); });

        // Iterate m_LayerStack backwards: from the end (overlays) to the beginning (layers)
        // E.g.: ImGui will be Overlay, app and editor will be Layers. We want to capture ImGui events over other layer events.
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            // If overlay handled the event -> break, layers will not get it
            if (_event.IsHandled())
            {
                break;
            }
            (*it)->OnEvent(_event);
        }
    }

    void Application::Run()
    {
        while (m_bRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_puWindow->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* _layer)
    {
        m_LayerStack.PushLayer(_layer);
    }

    void Application::PushOverlay(Layer* _overlay)
    {
        m_LayerStack.PushOverlay(_overlay);
    }

    bool Application::OnWindowClose(WindowCloseEvent& _event)
    {
        m_bRunning = false;
        return true;
    }
}
