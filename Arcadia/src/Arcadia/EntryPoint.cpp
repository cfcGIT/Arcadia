#ifdef ARC_PLATFORM_WINDOWS

#include "arcpch.h" // No need because it's pch, but so that intellisense doesn't complain

#include <iostream>

#include "Arcadia/Application.h"

extern Arcadia::CApplication* Arcadia::CreateApplication();

int main(int argc, char** argv)
{
    Arcadia::CLog::Init();

#ifdef ARC_TRACK_MEMORY
    g_bCountAllocs = true;
#endif

    Arcadia::CApplication* pApp = Arcadia::CreateApplication();
    pApp->Run();
    delete pApp;

#ifdef ARC_TRACK_MEMORY
    g_bCountAllocs = false;
#endif

    // Check memory leaks
#ifdef ARC_TRACK_MEMORY
    for (int i = 0; i < g_iTotalAllocs; ++i)
    {
        const SMemoryData& oMemoryData = g_tMemoryData[i];
        ARC_CORE_WARN("Memory leak of {0} bytes from {1}({2})", oMemoryData.m_uSize, oMemoryData.m_pFile, oMemoryData.m_iLine);
    }
    ARC_CORE_ASSERT(g_iTotalAllocs == 0 && g_uTotalBytes == 0, "Memory leaks summary: {0} bytes in {1} leaks!", g_uTotalBytes, g_iTotalAllocs);
#endif
}

#endif
