//#include "arcpch.h"

#include "Application.h"

#include "Arcadia/Events/ApplicationEvent.h"
#include "Arcadia/Events/MouseEvent.h"
#include "Arcadia/Log.h"

namespace Arcadia
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent ev(1280, 720);
        MouseButtonPressedEvent mev(5);
        ARC_TRACE(ev);
        ARC_TRACE(mev);
        while (true);
    }
}
