#ifdef ARC_PLATFORM_WINDOWS

#include "arcpch.h" // No need because it's pch, but so that intellisense doesn't complain

#include <iostream>

#include "Arcadia/Application.h"

#include "Arcadia/Memory.h"

extern Arcadia::CApplication* Arcadia::CreateApplication();

int main(int argc, char** argv)
{
    Arcadia::CLog::Init();

    g_iInitialAllocs = g_iTotalAllocs;

    Arcadia::CApplication* pApp = Arcadia::CreateApplication();
    pApp->Run();
    delete pApp;

    g_iFinalAllocs = g_iTotalAllocs;

    // Check memory leaks
#ifdef ARC_TRACK_MEMORY
    ARC_CORE_ASSERT(g_iFinalAllocs == g_iInitialAllocs, "There are {0} memory leaks!!", g_iFinalAllocs - g_iInitialAllocs);
#endif
}

#endif
