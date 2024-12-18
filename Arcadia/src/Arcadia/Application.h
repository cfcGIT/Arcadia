#pragma once

#include "Arcadia/Core.h"
#include "Arcadia/LayerStack.h"
#include "Arcadia/Events/Event.h"
#include "Arcadia/Events/ApplicationEvent.h"

#include "Arcadia/Window.h"

namespace Arcadia
{
    class CApplication
    {
    public:
        CApplication();
        virtual ~CApplication();

        void OnEvent(CEvent& _oEvent);

        void Run();

        void PushLayer(CLayer* _pLayer);
        void PushOverlay(CLayer* _pOverlay);

        inline CWindow& GetWindow() { return *m_pWindow; }

    private:
        bool OnWindowClose(CWindowCloseEvent& _oEvent);

    private:
        std::unique_ptr<CWindow> m_pWindow;
        bool m_bRunning = true;
        CLayerStack m_oLayerStack;
    };

    // To be defined in the client
    CApplication* CreateApplication();
}

