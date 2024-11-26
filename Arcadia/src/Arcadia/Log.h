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

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_pCoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_pClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> m_pCoreLogger;
        static std::shared_ptr<spdlog::logger> m_pClientLogger;
    };
}

// Core log macros
#define ARC_CORE_TRACE(...) ::Arcadia::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ARC_CORE_INFO(...) ::Arcadia::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ARC_CORE_WARN(...) ::Arcadia::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ARC_CORE_ERROR(...) ::Arcadia::Log::GetCoreLogger()->error(__VA_ARGS__)
// ?
#define ARC_CORE_FATAL(...) ::Arcadia::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define ARC_TRACE(...) ::Arcadia::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ARC_INFO(...) ::Arcadia::Log::GetClientLogger()->info(__VA_ARGS__)
#define ARC_WARN(...) ::Arcadia::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ARC_ERROR(...) ::Arcadia::Log::GetClientLogger()->error(__VA_ARGS__)
// ?
#define ARC_FATAL(...) ::Arcadia::Log::GetClientLogger()->fatal(__VA_ARGS__)

// '::Arcadia' instead of 'Arcadia' to assure that is this Arcadia namespace (global namespace)