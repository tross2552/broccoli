#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace brcl
{

	class BRCL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

//Core Log Macros
#define BRCL_CORE_TRACE(...)   ::brcl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BRCL_CORE_INFO(...)    ::brcl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BRCL_CORE_WARN(...)    ::brcl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BRCL_CORE_ERROR(...)   ::brcl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BRCL_CORE_FATAL(...)   ::brcl::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define BRCL_TRACE(...)        ::brcl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BRCL_INFO(...)         ::brcl::Log::GetClientLogger()->info(__VA_ARGS__)
#define BRCL_WARN(...)         ::brcl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BRCL_ERROR(...)        ::brcl::Log::GetClientLogger()->error(__VA_ARGS__)
#define BRCL_FATAL(...)        ::brcl::Log::GetClientLogger()->fatal(__VA_ARGS__)