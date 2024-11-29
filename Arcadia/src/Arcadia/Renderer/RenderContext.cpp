#include "Arcadia/Renderer/RenderContext.h"
#include "Arcadia/Renderer/Vulkan/RenderContext_VK.h"

namespace Arcadia
{
    std::unique_ptr<RenderContext> RenderContext::Create()
    {
        // TODO: if vulkan
        return std::make_unique<RenderContext_VK>();
    }
}
