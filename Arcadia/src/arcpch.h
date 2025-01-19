#pragma once

#include <functional>
#include <memory>
#include <set>
#include <sstream>
#include <stdint.h>
#include <string>
#include <vector>

#ifdef ARC_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include "Arcadia/Core/Core.h"
#include "Arcadia/Core/Memory.h"
#include "Arcadia/Log.h"

// TODO: Include if vulkan?
#include "vulkan/vulkan.h"
#include "Arcadia/Renderer/Vulkan/VK_Error.h"