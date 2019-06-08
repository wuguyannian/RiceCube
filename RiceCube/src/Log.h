#pragma once

#include <spdlog/spdlog.h>

namespace RiceCube
{
	class Log
	{
	public:
		static void init();

		static std::shared_ptr<spdlog::logger> getLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

#define RICE_TRACE(...)		RiceCube::Log::getLogger()->trace(__VA_ARGS__)
#define RICE_INFO(...)		RiceCube::Log::getLogger()->info(__VA_ARGS__)
#define RICE_WARN(...)		RiceCube::Log::getLogger()->warn(__VA_ARGS__)
#define RICE_ERROR(...)		RiceCube::Log::getLogger()->error(__VA_ARGS__)
#define RICE_CRITICAL(...)	RiceCube::Log::getLogger()->critical(__VA_ARGS__)
