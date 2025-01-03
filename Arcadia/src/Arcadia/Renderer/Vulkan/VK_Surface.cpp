// TODO: Check back when I want to retrieve the presentation support for the device. https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Window_surface
#if 0
#include "Arcadia/Renderer/Vulkan/VK_Surface.h"

#include "Arcadia/Renderer/Vulkan/VK_Context.h"

#include "GLFW/glfw3.h"

namespace Arcadia
{
    namespace VK
    {
        CVK_Surface::CVK_Surface(const VkInstance& _oVKInstance)
        {
            m_pInstance = this;

            GLFWwindow* pGLFWwindow = CApplication::Get().GetWindow().GetGLFWwindow();
            ARC_VK_CHECK(glfwCreateWindowSurface(_oVKInstance, pGLFWwindow, nullptr, &m_oVKSurface), "Failed to create window surface!");
        }

        CVK_Surface::~CVK_Surface()
        {
            m_pInstance = nullptr;
        }

        CVK_Surface* CVK_Surface::Create(const VkInstance& _oVKInstance)
        {
            return arcnew CVK_Surface(_oVKInstance);
        }

        void CVK_Surface::Destroy()
        {
            VkInstance oVkInstance = CVK_Context::Get()->GetInstance();
            if (!oVkInstance || oVkInstance == VK_NULL_HANDLE)
            {
                ARC_VK_ERROR("The instance must be destroyed after the surface!");
                return;
            }
            vkDestroySurfaceKHR(oVkInstance, m_oSurface, nullptr);
            delete m_pInstance;
        }
    }
}
#endif