#pragma once

#include "arcpch.h"

namespace Arcadia
{
    class CRendererAPI
    {
    public:
        enum class EAPI
        {
            None = -1,
            Vulkan = 0,
            OpenGL = 1,
            DX12 = 2
        };

    public:
        virtual void Init() = 0;

        static EAPI GetAPI() { return m_oAPI; }
        static std::unique_ptr<CRendererAPI> Create();

    private:
        static EAPI m_oAPI;

    };
}