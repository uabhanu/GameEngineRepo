#include "Log.h"

namespace BhanuEngine
{
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger; //Looks like declaring twice once in header file and now, ask Sri
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger; // Same as above

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_ClientLogger = spdlog::stdout_color_mt("Bhanu Engine Application");
		s_ClientLogger->set_level(spdlog::level::trace);

		s_CoreLogger = spdlog::stdout_color_mt("Bhanu Engine");
		s_CoreLogger->set_level(spdlog::level::trace);
	}
}
