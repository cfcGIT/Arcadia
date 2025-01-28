#include "Arcadia/Renderer/Vulkan/VK_Surface.h"

#include "Arcadia/Application.h"
#include "Arcadia/Renderer/Renderer.h"
#include "Arcadia/Renderer/Vulkan/VK_Context.h"
#include "Arcadia/Renderer/Vulkan/VK_Global.h"
#include "Arcadia/Renderer/Vulkan/VK_RendererAPI.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    namespace VK
    {
        CVK_Surface::CVK_Surface()
        {
            ARC_VK_CHECK(glfwCreateWindowSurface(Arcadia::VK::CVK_Context::GetVKInstance(), Arcadia::CWindow::GetGLFWwindow(), nullptr, &m_oVKSurface), "Failed to create window surface!");
        }

        CVK_Surface::~CVK_Surface()
        {
            vkDestroySurfaceKHR(Arcadia::VK::CVK_Context::GetVKInstance(), m_oVKSurface, nullptr);
        }
    }
}