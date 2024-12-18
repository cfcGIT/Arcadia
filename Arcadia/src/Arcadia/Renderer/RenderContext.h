#pragma once

#include "Arcadia/Core.h"

namespace Arcadia
{
    class CRenderContext
    {
    public:
        virtual ~CRenderContext() = default;

        virtual void Init() = 0;

        static std::unique_ptr<CRenderContext> Create();

        virtual void InitGUI() = 0;
    };
}