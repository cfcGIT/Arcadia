#include "Arcadia/Renderer/Vulkan/VK_Surface.h"

#include "Arcadia/Application.h"
#include "Arcadia/Core/Global.h"
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
            ARC_VK_CHECK(glfwCreateWindowSurface(*Arcadia::VKGlobal::g_pVKInstance, Arcadia::Global::g_pGLFWwindow, nullptr, &m_oVKSurface), "Failed to create window surface!");
            Arcadia::VKGlobal::g_pVKSurface = &m_oVKSurface;
        }

        CVK_Surface::~CVK_Surface()
        {
            vkDestroySurfaceKHR(*Arcadia::VKGlobal::g_pVKInstance, m_oVKSurface, nullptr);
        }
    }
}