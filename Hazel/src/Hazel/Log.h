#pragma once
#include "Core.h"

//As SubModule, when clone will automatically clone remote submodule
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"//for custom types log

namespace Hazel
{
	class HAZEL_API Log
	{
	public:
		Log();

		~Log();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_core_logger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_client_logger; }

	private:
		static std::shared_ptr<spdlog::logger> m_client_logger;
		static std::shared_ptr<spdlog::logger> m_core_logger;
	};
}

//Macro could easy be strip for distribution build 
//****Variadic Macro****//
#define HZ_LOG_CORE_ERROR(...)   ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)//__VA_ARGS__ means multiple arguments for macro
#define HZ_LOG_CORE_WARN(...)    ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_LOG_CORE_INFO(...)    ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_LOG_CORE_TRACE(...)   ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_LOG_CORE_FATAL(...)   ::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)
//Client Logger				+ ------------ - < -refers to------------- +
#define	HZ_LOG_ERROR(...) ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define	HZ_LOG_WARN(...)  ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define	HZ_LOG_INFO(...)  ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define	HZ_LOG_TRACE(...) ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define	HZ_LOG_FATAL(...) ::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)
