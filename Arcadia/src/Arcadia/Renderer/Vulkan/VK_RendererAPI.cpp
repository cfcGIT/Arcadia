#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"

#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_Surface.h"
#include "Arcadia/Renderer/Vulkan/VK_SwapChain.h"

namespace Arcadia
{
    namespace VK
    {
        void CVK_RendererAPI::Init()
        {
            InitRenderContext();
            CreateSurface();
            CreateSwapChain();
            // TODO: Create render pass
            // ...
        }

        void CVK_RendererAPI::InitRenderContext()
        {
            m_pContext = arcnew CVK_Context();
            m_pContext->Init();
        }

        void CVK_RendererAPI::Shutdown()
        {
            // Delete swap chain
            delete m_pSwapChain;
            m_pSwapChain = nullptr;

            // Delete surface
            delete m_pSurface;
            m_pSurface = nullptr;

            // Delete context
            m_pContext->Destroy();
            delete m_pContext;
            m_pContext = nullptr;;
        }

        /**
        * @brief Create the surface to establish the connection between Vulkan and the window system (https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Window_surface)
        */
        void CVK_RendererAPI::CreateSurface()
        {
            m_pSurface = arcnew CVK_Surface();
            ARC_VK_INFO("Window surface created!");
        }

        /**
        * @brief Create the swap chain, the infrastructure that will own the buffers we will render to before we visualize them on the screen (https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain)
        */
        void CVK_RendererAPI::CreateSwapChain()
        {
            m_pSwapChain = arcnew CVK_SwapChain();
            ARC_VK_INFO("Swap chain created!");
        }
    }
}
