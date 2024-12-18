#pragma once

#include "Arcadia/Renderer/RendererAPI.h"

namespace Arcadia
{
    class CRenderCommand
    {
    public:
        static void Init();

    private:
        static std::unique_ptr<CRendererAPI> m_oRendererAPI;
    };
}