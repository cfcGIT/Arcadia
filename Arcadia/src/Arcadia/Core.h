#pragma once

#ifdef ARC_PLATFORM_WINDOWS
    #ifdef ARC_BUILD_DLL
        #define ARCADIA_API __declspec(dllexport)
    #else
        #define ARCADIA_API __declspec(dllimport)
    #endif
#else
    #error Arcadia only supports windows!
#endif