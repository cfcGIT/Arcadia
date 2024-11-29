#include "Arcadia/Renderer/Vulkan/RenderContext_VK.h"
#include "Arcadia/Renderer/Vulkan/VK_Base.h"

namespace Arcadia
{
    RenderContext_VK::RenderContext_VK()
    {
    }

    void RenderContext_VK::Init()
    {       
        // Create instance
        VkResult res = Arcadia::VK::CreateInstance(m_vkInstance);
        Arcadia::VK::CheckResult(res, "Failed to create vulkan instance!", __FILE__, __LINE__);
        ARC_VK_INFO("Vulkan instance created!");

        // TODO: Select physical device
        // ...
        
        // TODO: Create logical device
        // ...
    }
}