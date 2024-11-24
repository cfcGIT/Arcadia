
#include "WindowsWindow.h"

namespace Arcadia
{
    static bool bGLFWInitialized = false;

    Window* Window::Create(const WindowProps& _windowProps)
    {
        return new WindowsWindow(_windowProps);
    }

    WindowsWindow::WindowsWindow(const WindowProps& _windowProps)
    {
        Init(_windowProps);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }


    void WindowsWindow::Init(const WindowProps& _windowProps)
    {
        m_WindowData.m_WindowProps = _windowProps;

        ARC_CORE_INFO("WindowsWindow create: {0} ({1}, {2})", _windowProps.m_sTitle, _windowProps.m_uWidth, _windowProps.m_uHeight);

        if (!bGLFWInitialized)
        {
            int iSuccess = glfwInit();
            ARC_CORE_ASSERT(iSuccess, "Could not initialize GLFW!");
            bGLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)_windowProps.m_uWidth, (int)_windowProps.m_uHeight, _windowProps.m_sTitle.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        SetVSync(true);



    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::SetVSync(bool _bEnabled)
    {
        glfwSwapInterval((_bEnabled) ? 1 : 0);
        m_WindowData.m_bVsync = _bEnabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_WindowData.m_bVsync;
    }




}
