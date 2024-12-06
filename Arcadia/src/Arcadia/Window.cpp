#include "Arcadia/Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Arcadia
{
    CWindow* CWindow::Create(const SWindowProps& _oWindowProps)
    {
#ifdef ARC_PLATFORM_WINDOWS
        return new CWindowsWindow(_oWindowProps);
#else
        ARC_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
#endif
    }
}