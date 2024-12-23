#pragma once

// TODO: include if vulkan
#include "Arcadia/Renderer/Vulkan/VK_Error.h"

// TODO: Support other OS
#ifndef ARC_PLATFORM_WINDOWS
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

// TODO: define if vulkan
#define ARC_VK_CHECK(res, msg) Arcadia::VK::_CheckVKResult(__FILE__, __LINE__, res, msg)