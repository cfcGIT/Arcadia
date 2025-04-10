#pragma once

#include "Arcadia/LayerStack.h"
#include "Arcadia/Renderer/RendererAPI.h"
#include "Arcadia/Window.h"

namespace Arcadia
{
    class CEvent;
    class CLayer;
    class CRenderer;
    class CWindowCloseEvent;

    class CApplication
    {
    public:
        CApplication();
        virtual ~CApplication();

        void OnEvent(CEvent& _oEvent);

        void Run();

        void PushLayer(CLayer* _pLayer);
        void PushOverlay(CLayer* _pOverlay);

        inline CWindow* GetWindow() const { return m_pWindow; }

        inline static CApplication* Get() { return m_pInstance; }

        inline CRenderer* GetRenderer() const { return m_pRenderer; }

    private:
        bool OnWindowClose(CWindowCloseEvent& _oEvent);

    private:
        CWindow* m_pWindow = nullptr;
        bool m_bRunning = true;
        CLayerStack m_oLayerStack;

        inline static CApplication* m_pInstance = nullptr;

        CRenderer* m_pRenderer = nullptr;
    };

    // To be defined in the client
    CApplication* CreateApplication();
}

