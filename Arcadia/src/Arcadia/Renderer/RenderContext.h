#pragma once

#include "Arcadia/Core.h"

namespace Arcadia
{
    class RenderContext
    {
    public:
        virtual ~RenderContext() = default;

        virtual void Init() = 0;

        static std::unique_ptr<RenderContext> Create();
    };
}