#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Arcadia
{
    std::shared_ptr<spdlog::logger> Log::m_psCoreLogger;
    std::shared_ptr<spdlog::logger> Log::m_psClientLogger;
    std::shared_ptr<spdlog::logger> Log::m_psVulkanLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_psCoreLogger = spdlog::stdout_color_mt("ARCADIA");
        m_psCoreLogger->set_level(spdlog::level::trace);

        m_psClientLogger = spdlog::stdout_color_mt("APP");
        m_psClientLogger->set_level(spdlog::level::trace);

        m_psVulkanLogger = spdlog::stdout_color_mt("VULKAN");
        m_psVulkanLogger->set_level(spdlog::level::trace);

    }
}
