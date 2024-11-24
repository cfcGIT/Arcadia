//#include "arcpch.h"

#include "Application.h"

#include "Arcadia/Events/ApplicationEvent.h"
#include "Arcadia/Events/MouseEvent.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
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
}
