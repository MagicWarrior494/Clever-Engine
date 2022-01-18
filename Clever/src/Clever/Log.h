#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Clever {

	class CLEVER_API Log
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

//Core log macros
#define CV_CORE_ERROR(...) ::Clever::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CV_CORE_WARN(...)  ::Clever::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CV_CORE_INFO(...)  ::Clever::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CV_CORE_TRACE(...) ::Clever::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define CV_ERROR(...) ::Clever::Log::GetClientLogger()->error(__VA_ARGS__)
#define CV_WARN(...)  ::Clever::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CV_INFO(...)  ::Clever::Log::GetClientLogger()->info(__VA_ARGS__)
#define CV_TRACE(...) ::Clever::Log::GetClientLogger()->trace(__VA_ARGS__)