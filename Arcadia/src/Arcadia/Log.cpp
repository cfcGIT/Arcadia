
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Arcadia
{
    std::shared_ptr<spdlog::logger> Log::m_pCoreLogger;
    std::shared_ptr<spdlog::logger> Log::m_pClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_pCoreLogger = spdlog::stdout_color_mt("ARCADIA");
        m_pCoreLogger->set_level(spdlog::level::trace);

        m_pClientLogger = spdlog::stdout_color_mt("APP");
        m_pClientLogger->set_level(spdlog::level::trace);

    }
}
