#pragma once

#include "Arcadia/Core.h"

#include "spdlog/spdlog.h"
// Git reference: https://github.com/gabime/spdlog
//  - Format: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
//  - fmt syntax: https://fmt.dev/latest/syntax/

namespace Arcadia
{
    class CLog
    {
    public:
        enum class ELogLevel
        {
            LOG_TRACE = 0, // Critical + Error + Warning + Info + Debug + Trace
            LOG_DEBUG, // Critical + Error + Warning + Info + Debug
            LOG_INFO, // Critical + Error + Warning + Info
            LOG_WARN, // Critical + Error + Warning
            LOG_ERROR, // Critical + Error
            LOG_CRITICAL, // Critical
            LOG_NONE
        };

    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_pCoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_pClientLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetVulkanLogger() { return m_pVulkanLogger; }

    private:
        static spdlog::level::level_enum GetSPDLogLevel();

    private:
        static std::shared_ptr<spdlog::logger> m_pCoreLogger;
        static std::shared_ptr<spdlog::logger> m_pClientLogger;
        static std::shared_ptr<spdlog::logger> m_pVulkanLogger;

        inline static CLog::ELogLevel m_oLogLevel = CLog::ELogLevel::LOG_TRACE; // TODO: CVar

    };
}

// Core log macros
#define ARC_CORE_TRACE(...) ::Arcadia::CLog::GetCoreLogger()->trace(__VA_ARGS__)
#define ARC_CORE_DEBUG(...) ::Arcadia::CLog::GetCoreLogger()->debug(__VA_ARGS__)
#define ARC_CORE_INFO(...) ::Arcadia::CLog::GetCoreLogger()->info(__VA_ARGS__)
#define ARC_CORE_WARN(...) ::Arcadia::CLog::GetCoreLogger()->warn(__VA_ARGS__)
#define ARC_CORE_ERROR(...) ::Arcadia::CLog::GetCoreLogger()->error(__VA_ARGS__)
#define ARC_CORE_CRITICAL(...) ::Arcadia::CLog::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ARC_TRACE(...) ::Arcadia::CLog::GetClientLogger()->trace(__VA_ARGS__)
#define ARC_DEBUG(...) ::Arcadia::CLog::GetClientLogger()->debug(__VA_ARGS__)
#define ARC_INFO(...) ::Arcadia::CLog::GetClientLogger()->info(__VA_ARGS__)
#define ARC_WARN(...) ::Arcadia::CLog::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_ERROR(...) ::Arcadia::CLog::GetClientLogger()->error(__VA_ARGS__)
#define ARC_CRITICAL(...) ::Arcadia::CLog::GetClientLogger()->critical(__VA_ARGS__)

// Vulkan log macros
#define ARC_VK_TRACE(...) ::Arcadia::CLog::GetVulkanLogger()->trace(__VA_ARGS__)
#define ARC_VK_DEBUG(...) ::Arcadia::CLog::GetVulkanLogger()->debug(__VA_ARGS__)
#define ARC_VK_INFO(...) ::Arcadia::CLog::GetVulkanLogger()->info(__VA_ARGS__)
#define ARC_VK_WARN(...) ::Arcadia::CLog::GetVulkanLogger()->warn(__VA_ARGS__)
#define ARC_VK_ERROR(...) ::Arcadia::CLog::GetVulkanLogger()->error(__VA_ARGS__)
#define ARC_VK_CRITICAL(...) ::Arcadia::CLog::GetVulkanLogger()->critical(__VA_ARGS__)

// '::Arcadia' instead of 'Arcadia' to assure that is this Arcadia namespace (global namespace)