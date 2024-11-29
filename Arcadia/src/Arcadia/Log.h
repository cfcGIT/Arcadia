#pragma once

#include "Arcadia/Core.h"

#include "spdlog/spdlog.h"
// Git reference: https://github.com/gabime/spdlog
//  - Format: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
//  - fmt syntax: https://fmt.dev/latest/syntax/

namespace Arcadia
{
    class ARCADIA_API Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_psCoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_psClientLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetVulkanLogger() { return m_psVulkanLogger; }

    private:
        static std::shared_ptr<spdlog::logger> m_psCoreLogger;
        static std::shared_ptr<spdlog::logger> m_psClientLogger;
        static std::shared_ptr<spdlog::logger> m_psVulkanLogger;
    };
}

// Core log macros
#define ARC_CORE_TRACE(...) ::Arcadia::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ARC_CORE_INFO(...) ::Arcadia::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ARC_CORE_WARN(...) ::Arcadia::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ARC_CORE_ERROR(...) ::Arcadia::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ARC_CORE_CRITICAL(...) ::Arcadia::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ARC_TRACE(...) ::Arcadia::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ARC_INFO(...) ::Arcadia::Log::GetClientLogger()->info(__VA_ARGS__)
#define ARC_WARN(...) ::Arcadia::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_ERROR(...) ::Arcadia::Log::GetClientLogger()->error(__VA_ARGS__)
#define ARC_CRITICAL(...) ::Arcadia::Log::GetClientLogger()->critical(__VA_ARGS__)

// Vulkan log macros
#define ARC_VK_TRACE(...) ::Arcadia::Log::GetVulkanLogger()->trace(__VA_ARGS__)
#define ARC_VK_INFO(...) ::Arcadia::Log::GetVulkanLogger()->info(__VA_ARGS__)
#define ARC_VK_WARN(...) ::Arcadia::Log::GetVulkanLogger()->warn(__VA_ARGS__)
#define ARC_VK_ERROR(...) ::Arcadia::Log::GetVulkanLogger()->error(__VA_ARGS__)
#define ARC_VK_CRITICAL(...) ::Arcadia::Log::GetVulkanLogger()->critical(__VA_ARGS__)

// '::Arcadia' instead of 'Arcadia' to assure that is this Arcadia namespace (global namespace)