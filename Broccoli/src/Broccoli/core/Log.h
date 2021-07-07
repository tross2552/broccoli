#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace brcl
{

	class BRCL_API Log
	{
	public:
		static void Init()
		{
			spdlog::set_pattern("%^[%T] %n: %v%$");

			s_CoreLogger = spdlog::stdout_color_mt("BRCL");
			s_CoreLogger->set_level(spdlog::level::level_enum::trace);
			s_ClientLogger = spdlog::stdout_color_mt("APP");
			s_ClientLogger->set_level(spdlog::level::level_enum::trace);
		}

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		
	private:
		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
		inline static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core Log Macros
#define BRCL_CORE_TRACE(...)      ::brcl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BRCL_CORE_INFO(...)       ::brcl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BRCL_CORE_WARN(...)       ::brcl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BRCL_CORE_ERROR(...)      ::brcl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BRCL_CORE_CRITICAL(...)   ::brcl::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client Log Macros
#define BRCL_TRACE(...)           ::brcl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BRCL_INFO(...)            ::brcl::Log::GetClientLogger()->info(__VA_ARGS__)
#define BRCL_WARN(...)            ::brcl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BRCL_ERROR(...)           ::brcl::Log::GetClientLogger()->error(__VA_ARGS__)
#define BRCL_CRITICAL(...)        ::brcl::Log::GetClientLogger()->critical(__VA_ARGS__)