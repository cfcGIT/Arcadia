#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_Engine.h"

namespace Arcadia
{
    CVK_Context::CVK_Context()
    {
    }

    void CVK_Context::Init()
    {       
        // Create instance
        ARC_VK_CHECK(Arcadia::VK::CreateInstance(m_oVKInstance), "Failed to create vulkan instance!");
        ARC_VK_INFO("Vulkan instance created!");

        // TODO: Select physical device
        // ...
        
        // TODO: Create logical device
        // ...
    }
}