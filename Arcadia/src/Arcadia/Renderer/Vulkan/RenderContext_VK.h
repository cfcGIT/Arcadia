#pragma once

#include "Arcadia/Renderer/RenderContext.h"
#include "vulkan/vulkan.h"

namespace Arcadia
{
    class RenderContext_VK : public RenderContext
    {
    public:
        RenderContext_VK();

        virtual void Init() override;

    private:
        VkInstance m_vkInstance = VK_NULL_HANDLE;
    };
}