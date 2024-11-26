
#include "Arcadia/Application.h"
#include "Arcadia/Events/MouseEvent.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback([this](Event& _e) { OnEvent(_e); });
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& _e)
    {
        // Dispatch: if WindowCloseEvent -> OnWindowClose
        EventDispatcher dispatcher(_e);
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& _e) -> bool { return OnWindowClose(_e); });

        // Iterate m_LayerStack backwards: from the end (overlays) to the beginning (layers)
        // E.g.: ImGui will be Overlay, app and editor will be Layers. We want to capture ImGui events over other layer events.
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            // If overlay handled the event -> break, layers will not get it
            if (_e.IsHandled())
            {
                break;
            }
            (*it)->OnEvent(_e);
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

            m_Window->OnUpdate();
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

    bool Application::OnWindowClose(WindowCloseEvent& _e)
    {
        m_bRunning = false;
        return true;
    }
}
