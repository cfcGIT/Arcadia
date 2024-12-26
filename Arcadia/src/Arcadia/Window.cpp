#include "Arcadia/Window.h"

#include "Arcadia/Events/ApplicationEvent.h"
#include "Arcadia/Events/KeyEvent.h"
#include "Arcadia/Events/MouseEvent.h"
#include "Arcadia/Renderer/RenderContext.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    static bool s_bGLFWInitialized = false;

    static void GLFWErrorCallback(int _iErrorCode, const char* _sDescription)
    {
        ARC_CORE_ERROR("GLFW Error ({0}): {1}", _iErrorCode, _sDescription);
    }

    CWindow::CWindow()
    {
        Init(SWindowProps());
    }

    CWindow::CWindow(const SWindowProps& _oWindowProps)
    {
        Init(_oWindowProps);
    }

    CWindow::~CWindow()
    {
        Shutdown();
    }

    void CWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_pGLFWWindow);
    }

    void CWindow::InitRenderContext()
    {
        // * Render context
        m_pRenderContext = CRenderContext::Create();
        m_pRenderContext->Init();
    }

    void CWindow::Init(const SWindowProps& _oWindowProps)
    {
        m_oWindowData.m_oWindowProps = _oWindowProps;

        if (!s_bGLFWInitialized)
        {
            int iSuccess = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
            ARC_CORE_ASSERT(iSuccess, "Could not initialize GLFW!");
            s_bGLFWInitialized = true;
        }

        m_pGLFWWindow = glfwCreateWindow((int)_oWindowProps.m_uWidth, (int)_oWindowProps.m_uHeight, _oWindowProps.m_sTitle.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_pGLFWWindow);
        glfwSetWindowUserPointer(m_pGLFWWindow, &m_oWindowData);
        // TODO: glfwSetFramebufferSizeCallback(m_Window, framebufferResizeCallback);
        SetVSync(true);

        ARC_CORE_INFO("GFLW window created: {0} ({1}, {2})", _oWindowProps.m_sTitle, _oWindowProps.m_uWidth, _oWindowProps.m_uHeight);

        // * Set GLFW callbacks
        // App events
        glfwSetWindowSizeCallback(m_pGLFWWindow, OnWindowResizeEvent);
        glfwSetWindowCloseCallback(m_pGLFWWindow, OnWindowCloseEvent);
        glfwSetDropCallback(m_pGLFWWindow, OnDropFilesEvent);
        //TODO: glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow* _window) ...

        // Mouse events
        glfwSetCursorPosCallback(m_pGLFWWindow, OnMouseMovedEvent);
        glfwSetMouseButtonCallback(m_pGLFWWindow, OnMouseButtonEvent);
        glfwSetScrollCallback(m_pGLFWWindow, OnMouseScrolledEvent);

        // Key events
        glfwSetKeyCallback(m_pGLFWWindow, OnKeyEvent);
    }

    void CWindow::Shutdown()
    {
        glfwDestroyWindow(m_pGLFWWindow);
        glfwTerminate();
        delete m_pRenderContext;
    }

    void CWindow::OnWindowResizeEvent(GLFWwindow* _pGLFWWindow, int _iWidth, int _iHeight)
    {
        SWindowData& oWindowData = *(SWindowData*)glfwGetWindowUserPointer(_pGLFWWindow);
        oWindowData.m_oWindowProps.m_uWidth = (uint32_t)_iWidth;
        oWindowData.m_oWindowProps.m_uHeight = (uint32_t)_iHeight;

        CWindowResizeEvent oEvent(_iWidth, _iHeight);
        oWindowData.m_oEventCallback(oEvent); // Calls event callback function setted in SetEventCallback. E.g.: OnEvent setted in Application ctor
    }

    void CWindow::OnWindowCloseEvent(GLFWwindow* _pGLFWWindow)
    {
        SWindowData& oWindowData = *(SWindowData*)glfwGetWindowUserPointer(_pGLFWWindow);

        CWindowCloseEvent oEvent;
        oWindowData.m_oEventCallback(oEvent);
    }

    void CWindow::OnDropFilesEvent(GLFWwindow* _pGLFWWindow, int _iPathCount, const char* _sPaths[])
    {
        SWindowData& oWindowData = *(SWindowData*)glfwGetWindowUserPointer(_pGLFWWindow);

        CDropFilesEvent oEvent(_iPathCount, _sPaths);
        oWindowData.m_oEventCallback(oEvent);
    }

    void CWindow::OnMouseMovedEvent(GLFWwindow* _pGLFWWindow, double _dXPos, double _dYPos)
    {
        SWindowData& oWindowData = *(SWindowData*)glfwGetWindowUserPointer(_pGLFWWindow);

        CMouseMovedEvent oEvent((float)_dXPos, (float)_dYPos);
        oWindowData.m_oEventCallback(oEvent);
    }

    void CWindow::OnMouseButtonEvent(GLFWwindow* _pGLFWWindow, int _iButton, int _iAction, int _iMods)
    {
        SWindowData& oWindowData = *(SWindowData*)glfwGetWindowUserPointer(_pGLFWWindow);

        switch (_iAction)
        {
            case GLFW_PRESS:
            {
                CMouseButtonPressedEvent oEvent(_iButton);
                oWindowData.m_oEventCallback(oEvent);
                break;
            }
            case GLFW_RELEASE:
            {
                CMouseButtonReleasedEvent oEvent(_iButton);
                oWindowData.m_oEventCallback(oEvent);
                break;
            }
        }
    }

    void CWindow::OnMouseScrolledEvent(GLFWwindow* _pGLFWWindow, double _dXOffset, double _dYOffset)
    {
        SWindowData& oWindowData = *(SWindowData*)glfwGetWindowUserPointer(_pGLFWWindow);

        CMouseScrolledEvent event((float)_dXOffset, (float)_dYOffset);
        oWindowData.m_oEventCallback(event);
    }

    void CWindow::OnKeyEvent(GLFWwindow* _pGLFWWindow, int _iKey, int _iScancode, int _iAction, int _iMods)
    {
        SWindowData& oWindowData = *(SWindowData*)glfwGetWindowUserPointer(_pGLFWWindow);

        switch (_iAction)
        {
            case GLFW_PRESS:
            {
                CKeyPressedEvent oEvent(_iKey, 0);
                oWindowData.m_oEventCallback(oEvent);
                break;
            }
            case GLFW_RELEASE:
            {
                CKeyReleasedEvent oEvent(_iKey);
                oWindowData.m_oEventCallback(oEvent);
                break;
            }
            case GLFW_REPEAT:
            {
                CKeyPressedEvent oEvent(_iKey, 1);
                oWindowData.m_oEventCallback(oEvent);
                break;
            }
        }
    }

    void CWindow::SetVSync(bool _bEnabled)
    {
        glfwSwapInterval((_bEnabled) ? 1 : 0);
        m_oWindowData.m_bVsync = _bEnabled;
    }
}