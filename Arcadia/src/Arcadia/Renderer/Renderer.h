#pragma once

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/RendererAPI.h"

namespace Arcadia
{
    class CRenderer
    {
    public:
        inline CRendererAPI& GetRendererAPI() const { return *m_pRendererAPI; }

        void Init();
        void Shutdown();

        CRendererAPI::EAPI GetAPI() { return m_pRendererAPI->GetAPI(); }

    private:
        std::unique_ptr<CRendererAPI> m_pRendererAPI;
    };
}