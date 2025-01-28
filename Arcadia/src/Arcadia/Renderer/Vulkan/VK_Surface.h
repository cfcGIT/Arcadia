#pragma once

namespace Arcadia
{
    namespace VK
    {
        class CVK_Surface
        {
        public:
            CVK_Surface();
            ~CVK_Surface();

            inline static VkSurfaceKHR GetVKSurface() { return m_oVKSurface; }

        private:
            inline static VkSurfaceKHR m_oVKSurface = VK_NULL_HANDLE;
        };
    }
}