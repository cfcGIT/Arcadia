#pragma once
// TODO: Check back when I want to retrieve the presentation support for the device. https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Window_surface
# if 0
class GLFWwindow;

#include "vulkan/vulkan.h"

namespace Arcadia
{
    namespace VK
    {
        class CVK_Surface
        {
        public:
            CVK_Surface(const VkInstance& _oVkInstance);
            ~CVK_Surface();

            static CVK_Surface* Create(const VkInstance& _oVkInstance);
            void Destroy();

            inline static CVK_Surface& Get() { return *m_pInstance; }

            inline VkSurfaceKHR GetVkSurface() const { return m_oSurface; }

        private:
            VkSurfaceKHR m_oSurface = VK_NULL_HANDLE;

            inline static CVK_Surface* m_pInstance = nullptr; // XXX: I don't like this very much
        };
    }
}
#endif