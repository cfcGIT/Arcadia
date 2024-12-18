#pragma once

#include "Arcadia/Renderer/RenderContext.h"
#include "vulkan/vulkan.h"

namespace Arcadia
{
    class CVK_Context : public CRenderContext
    {
    public:
        CVK_Context();

        virtual void Init() override;

        virtual void InitGUI() override;

        inline VkInstance GetInstance() const { return m_oVKInstance; }




    private:
        VkInstance m_oVKInstance = VK_NULL_HANDLE; 
    };
}