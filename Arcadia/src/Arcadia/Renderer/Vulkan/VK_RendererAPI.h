#pragma once

#include "Arcadia/Renderer/RendererAPI.h"

namespace Arcadia
{
    class CVK_RendererAPI : public CRendererAPI
    {
    public:
        virtual void Init() override;
    };
}