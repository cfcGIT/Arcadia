
#include "Platform/Windows/WindowsWindow.h"

#include "Arcadia/Events/ApplicationEvent.h"
#include "Arcadia/Events/KeyEvent.h"
#include "Arcadia/Events/MouseEvent.h"

namespace Arcadia
{
    static bool bGLFWInitialized = false;

    static void GLFWErrorCallback(int _iErrorCode, const char* _sDescription)
    {
        ARC_CORE_ERROR("GLFW Error ({0}): {1}", _iErrorCode, _sDescription);
    }

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
            glfwSetErrorCallback(GLFWErrorCallback);
            ARC_CORE_ASSERT(iSuccess, "Could not initialize GLFW!");
            bGLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)_windowProps.m_uWidth, (int)_windowProps.m_uHeight, _windowProps.m_sTitle.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        // TODO: glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);
        SetVSync(true);

        // * Set GLFW callbacks
        // App events
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* _window, int _iWidth, int _iHeight)
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(_window);
                windowData.m_WindowProps.m_uWidth = _iWidth;
                windowData.m_WindowProps.m_uHeight = _iHeight;

                WindowResizeEvent event(_iWidth, _iHeight);
                windowData.m_EventCallback(event); // Calls event callback function setted in SetEventCallback. E.g.: OnEvent setted in Application ctor
            }
        );
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* _window)
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(_window);

                WindowCloseEvent event;
                windowData.m_EventCallback(event);
            }
        );
        glfwSetDropCallback(m_Window, [](GLFWwindow* _window, int _iPathCount, const char* _sPaths[])
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(_window);

                DropFilesEvent event(_iPathCount, _sPaths);
                windowData.m_EventCallback(event);
            }
        );
        //TODO: glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow* _window) ...

        // Mouse events
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* _window, double _dXPos, double _dYPos)
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(_window);

                MouseMovedEvent event((float)_dXPos, (float)_dYPos);
                windowData.m_EventCallback(event);

            }
        );
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* _window, int _iButton, int _iAction, int _iMods)
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(_window);

                switch (_iAction)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event(_iButton);
                        windowData.m_EventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event(_iButton);
                        windowData.m_EventCallback(event);
                        break;
                    }
                }
            }
        );
        glfwSetScrollCallback(m_Window, [](GLFWwindow* _window, double _dXOffset, double _dYOffset)
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(_window);

                MouseScrolledEvent event((float)_dXOffset, (float)_dYOffset);
                windowData.m_EventCallback(event);
            }
        );

        // Key events
        glfwSetKeyCallback(m_Window, [](GLFWwindow* _window, int _iKey, int _iScancode, int _iAction, int _iMods)
            {
                WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(_window);

                switch (_iAction)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent event(_iKey, 0);
                        windowData.m_EventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent event(_iKey);
                        windowData.m_EventCallback(event);
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent event(_iKey, 1);
                        windowData.m_EventCallback(event);
                        break;
                    }
                }
            }
        );
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
