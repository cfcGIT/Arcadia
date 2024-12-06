#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Arcadia
{
    std::shared_ptr<spdlog::logger> CLog::m_pCoreLogger;
    std::shared_ptr<spdlog::logger> CLog::m_pClientLogger;
    std::shared_ptr<spdlog::logger> CLog::m_pVulkanLogger;

    void CLog::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_pCoreLogger = spdlog::stdout_color_mt("ARCADIA");
        m_pCoreLogger->set_level(spdlog::level::trace);

        m_pClientLogger = spdlog::stdout_color_mt("APP");
        m_pClientLogger->set_level(spdlog::level::trace);

        m_pVulkanLogger = spdlog::stdout_color_mt("VULKAN");
        m_pVulkanLogger->set_level(spdlog::level::trace);

    }
}
