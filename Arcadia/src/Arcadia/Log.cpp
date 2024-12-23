#include "Arcadia/Log.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Arcadia
{
    std::shared_ptr<spdlog::logger> CLog::m_pCoreLogger;
    std::shared_ptr<spdlog::logger> CLog::m_pClientLogger;
    std::shared_ptr<spdlog::logger> CLog::m_pVulkanLogger;

    void CLog::Init()
    {
        spdlog::level::level_enum oSPDLogLevel = GetSPDLogLevel();
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_pCoreLogger = spdlog::stdout_color_mt("ARCADIA");
        m_pCoreLogger->set_level(oSPDLogLevel);

        m_pClientLogger = spdlog::stdout_color_mt("APP");
        m_pClientLogger->set_level(oSPDLogLevel);

        m_pVulkanLogger = spdlog::stdout_color_mt("VULKAN");
        m_pVulkanLogger->set_level(oSPDLogLevel);

    }

    spdlog::level::level_enum CLog::GetSPDLogLevel()
    {
        switch (m_oLogLevel)
        {
            case CLog::ELogLevel::LOG_TRACE: return spdlog::level::trace;
            case CLog::ELogLevel::LOG_DEBUG: return spdlog::level::debug;
            case CLog::ELogLevel::LOG_INFO: return spdlog::level::info;
            case CLog::ELogLevel::LOG_WARN: return spdlog::level::warn;
            case CLog::ELogLevel::LOG_ERROR: return spdlog::level::err;
            case CLog::ELogLevel::LOG_CRITICAL: return spdlog::level::critical;
            default: return spdlog::level::off;
        }
    }
}
