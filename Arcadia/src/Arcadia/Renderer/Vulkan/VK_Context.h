#pragma once

#include "Arcadia/Renderer/RenderContext.h"
#include "vulkan/vulkan.h"

namespace Arcadia
{
    class VK_Context : public RenderContext
    {
    public:
        VK_Context();

        virtual void Init() override;

    private:
        VkInstance m_vkInstance = VK_NULL_HANDLE;
    };
}