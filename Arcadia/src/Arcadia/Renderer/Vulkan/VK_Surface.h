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

        private:
            VkSurfaceKHR m_oVKSurface = VK_NULL_HANDLE;
        };
    }
}