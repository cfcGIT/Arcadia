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

#ifdef ARC_ENABLE_ASSERT
#define ARC_CORE_ASSERT(x, ...) { if (!(x)) { ARC_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
#define ARC_ASSERT(x, ...) { if (!(x)) { ARC_ERROR(__VA_ARGS__); __debugbreak(); } }
#define ARC_VK_ASSERT(x, ...) { if (!(x)) { ARC_VK_ERROR(__VA_ARGS__); __debugbreak(); } }
#else // Assert disabled
#define ARC_CORE_ASSERT(x, ...) { }
#define ARC_ASSERT(x, ...) { }
#define ARC_VK_ASSERT(x, ...) { }
#endif

#define BIT(x) (1 << x)