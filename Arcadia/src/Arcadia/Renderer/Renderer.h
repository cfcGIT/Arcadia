#pragma once

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/RendererAPI.h"

namespace Arcadia
{
    class CRenderer
    {
    public:
        inline static CRenderContext* GetContext() { return CApplication::Get().GetWindow().GetRenderContext(); }

        static void Init();
        static void Shutdown();

        static CRendererAPI::EAPI GetAPI() { return CRendererAPI::GetAPI(); }
    };
}