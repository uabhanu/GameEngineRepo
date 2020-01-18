#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> //You get an error when you remove this so for now, keep it
#include <spdlog/fmt/ostr.h>

#include "Core.h"

namespace BhanuEngine
{
	class ENGINE_API Log
	{
		private:
		    static std::shared_ptr<spdlog::logger> s_ClientLogger;
		    static std::shared_ptr<spdlog::logger> s_CoreLogger;
		public:
		    static void Init();
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	};
}

//Core Log Macros
#define ENGINE_CORE_TRACE(...) ::BhanuEngine::Log::GetCoreLogger()->trace(__VA_ARGS__) 
#define ENGINE_CORE_INFO(...) ::BhanuEngine::Log::GetCoreLogger()->info(__VA_ARGS__) 
#define ENGINE_CORE_WARN(...) ::BhanuEngine::Log::GetCoreLogger()->warn(__VA_ARGS__) 
#define ENGINE_CORE_ERROR(...) ::BhanuEngine::Log::GetCoreLogger()->error(__VA_ARGS__) 
#define ENGINE_CORE_FATAL(...) ::BhanuEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Core Log Macros
#define ENGINE_CLIENT_TRACE(...) ::BhanuEngine::Log::GetClientLogger()->trace(__VA_ARGS__) 
#define ENGINE_CLIENT_INFO(...) ::BhanuEngine::Log::GetClientLogger()->info(__VA_ARGS__) 
#define ENGINE_CLIENT_WARN(...) ::BhanuEngine::Log::GetClientLogger()->warn(__VA_ARGS__) 
#define ENGINE_CLIENT_ERROR(...) ::BhanuEngine::Log::GetClientLogger()->error(__VA_ARGS__) 
#define ENGINE_CLIENT_FATAL(...) ::BhanuEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

