#pragma once

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/RendererAPI.h"

namespace Arcadia
{
    class CRenderer
    {
    public:
        inline CRendererAPI* GetRendererAPI() const { return m_pRendererAPI; }

        void Init();
        void Shutdown();

        CRendererAPI::EAPI GetAPI() const { return m_pRendererAPI->GetAPI(); }

    private:
        CRendererAPI* m_pRendererAPI = nullptr;
    };
}