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
    g_uInitialBytes = g_uTotalBytes;

    Arcadia::CApplication* pApp = Arcadia::CreateApplication();
    pApp->Run();
    delete pApp;

    g_iFinalAllocs = g_iTotalAllocs;
    g_uFinalBytes = g_uTotalBytes;

    // Check memory leaks
#ifdef ARC_TRACK_MEMORY
    for(const auto& kb: g_mMemoryData)
    {
        SMemoryData oMemoryData = (SMemoryData)(kb.second);
        ARC_CORE_WARN("ARC memory leak of {0} bytes from {1}({2})", oMemoryData.m_uSize, oMemoryData.m_pFile, oMemoryData.m_iLine);
    }
    ARC_CORE_ASSERT(g_uFinalBytes == g_uInitialBytes, "ARC memory leaks summary: {0} bytes!!", g_uFinalBytes - g_uInitialBytes); // Memory leaks of arcnew
    ARC_CORE_ASSERT(g_iFinalAllocs == g_iInitialAllocs, "Total memory leaks: {0}!!", g_iFinalAllocs - g_iInitialAllocs); // Memory leaks of arcnew + new
#endif
}

#endif
