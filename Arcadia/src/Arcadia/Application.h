#pragma once

#include "Arcadia/Core.h"
#include "Arcadia/Events/ApplicationEvent.h"
#include "Arcadia/Events/Event.h"
#include "Arcadia/LayerStack.h"

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

        inline static CApplication& Get() { return *m_oApplication; }

    private:
        bool OnWindowClose(CWindowCloseEvent& _oEvent);

    private:
        std::unique_ptr<CWindow> m_pWindow;
        bool m_bRunning = true;
        CLayerStack m_oLayerStack;

        static CApplication* m_oApplication;
    };

    // To be defined in the client
    CApplication* CreateApplication();
}

