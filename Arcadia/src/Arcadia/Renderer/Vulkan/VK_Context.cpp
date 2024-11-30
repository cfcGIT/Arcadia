#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_Engine.h"

namespace Arcadia
{
    VK_Context::VK_Context()
    {
    }

    void VK_Context::Init()
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