//#include "arcpch.h"

#include "Application.h"

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

        ARC_CORE_TRACE("{0}", _e);
    }

    void Application::Run()
    {
        while (m_bRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& _e)
    {
        m_bRunning = false;
        return true;
    }
}
