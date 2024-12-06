#include "Arcadia/Renderer/RenderContext.h"
#include "Arcadia/Renderer/Vulkan/VK_Context.h"

namespace Arcadia
{
    std::unique_ptr<CRenderContext> CRenderContext::Create()
    {
        // TODO: if vulkan
        return std::make_unique<CVK_Context>();
    }
}
