#pragma once

#include "Arcadia/Renderer/RendererAPI.h"

namespace Arcadia
{
    class CRenderer
    {
    public:
        static void Init();
        static void Shutdown();

        static CRendererAPI::EAPI GetAPI() { return CRendererAPI::GetAPI(); }
    };
}