#include "Arcadia/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Arcadia
{
    Window* Window::Create(const WindowProps& _windowProps)
    {
#ifdef ARC_PLATFORM_WINDOWS
        return new WindowsWindow(_windowProps);
#else
        ARC_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
#endif
    }
}