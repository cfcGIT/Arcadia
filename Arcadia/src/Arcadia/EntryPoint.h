#pragma once

#ifdef ARC_PLATFORM_WINDOWS

#include "arcpch.h" // No need because it's pch, but so that intellisense doesn't complain

#include <iostream>

#include "Arcadia/Layer.h"

extern Arcadia::CApplication* Arcadia::CreateApplication();

int main(int argc, char** argv)
{
    Arcadia::CLog::Init();

    Arcadia::CApplication* pApp = Arcadia::CreateApplication();
    pApp->Run();
    delete pApp;
}


#endif
