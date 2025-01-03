#pragma once

namespace Arcadia
{
    class CRenderContext
    {
    public:
        virtual ~CRenderContext() = default;

        virtual void Init() = 0;
        virtual void InitGUI() = 0;
        virtual void Destroy() = 0;
    };
}