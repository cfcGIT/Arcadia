#pragma once

#include "Core.h"

namespace Arcadia
{
    class ARCADIA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in the client
    Application* CreateApplication();
}

