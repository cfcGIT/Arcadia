#pragma once

#include "Arcadia/Core.h"
#include "Arcadia/LayerStack.h"
#include "Arcadia/Events/Event.h"
#include "Arcadia/Events/ApplicationEvent.h"

#include "Arcadia/Window.h"

namespace Arcadia
{
    class ARCADIA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& _e);

        void Run();

        void PushLayer(Layer* _layer);
        void PushOverlay(Layer* _overlay);

    private:
        bool OnWindowClose(WindowCloseEvent& _e);

    private:
        std::unique_ptr<Window> m_Window;
        bool m_bRunning = true;

        LayerStack m_LayerStack;
    };

    // To be defined in the client
    Application* CreateApplication();
}

