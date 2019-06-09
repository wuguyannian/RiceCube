#include "ricepch.h"
#include "log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace RiceCube
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stdout_color_mt("Rice");
		s_Logger->set_level(spdlog::level::trace);
	}
}