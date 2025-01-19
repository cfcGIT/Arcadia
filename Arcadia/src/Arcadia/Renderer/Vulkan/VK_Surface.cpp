#include "Arcadia/Renderer/Vulkan/VK_Surface.h"

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/Renderer.h"
#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    namespace VK
    {
        CVK_Surface::CVK_Surface()
        {
            GLFWwindow* pGLFWwindow = CApplication::Get()->GetWindow()->GetGLFWwindow();
            const VkInstance* pVKInstance = ((CVK_RendererAPI*)CApplication::Get()->GetRenderer()->GetRendererAPI())->GetContext()->GetInstance();
            ARC_VK_CHECK(glfwCreateWindowSurface(*pVKInstance, pGLFWwindow, nullptr, &m_oVKSurface), "Failed to create window surface!");
        }

        CVK_Surface::~CVK_Surface()
        {
            const VkInstance* pVKInstance = ((CVK_RendererAPI*)CApplication::Get()->GetRenderer()->GetRendererAPI())->GetContext()->GetInstance();
            vkDestroySurfaceKHR(*pVKInstance, m_oVKSurface, nullptr);
        }
    }
}