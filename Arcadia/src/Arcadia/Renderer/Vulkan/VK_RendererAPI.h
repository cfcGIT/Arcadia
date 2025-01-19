#pragma once

#include "Arcadia/Renderer/RendererAPI.h"
//#include "Arcadia/Renderer/Vulkan/VK_Context.h"

namespace Arcadia
{
    namespace VK
    {
        class CVK_Context;
        class CVK_Surface;
        class CVK_SwapChain;

        class CVK_RendererAPI : public CRendererAPI
        {
        public:
            virtual void Init() override;
            virtual void InitRenderContext() override;
            virtual void Shutdown() override;

            inline CVK_Context* GetContext() const { return m_pContext; }
            inline CVK_Surface* GetSurface() const { return m_pSurface; }
            inline CVK_SwapChain* GetSwapChain() const { return m_pSwapChain; }

            void CreateSurface();
            void CreateSwapChain();

        private:
            CVK_Context* m_pContext = nullptr;
            CVK_Surface* m_pSurface = nullptr;
            CVK_SwapChain* m_pSwapChain = nullptr;
        };
    }
}