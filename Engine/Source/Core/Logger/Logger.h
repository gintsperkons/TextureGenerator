#pragma once
#include "Defines.h"
#include <cstdarg>

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1



#if TDEBUG == 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#endif

#if TRELEASE == 1 || TDIST == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif



namespace TextureGenEngine
{
	namespace Logger
	{
		enum class Level
		{
			FATAL = 0,
			ERR,
			WARN,
			INFO,
			DEBUG,
			TRACE
		};


		TAPI void Log(Logger::Level level, const char* format, ...);

#define LOG_FATAL(format, ...) TextureGenEngine::Logger::Log(TextureGenEngine::Logger::Level::FATAL, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) TextureGenEngine::Logger::Log(TextureGenEngine::Logger::Level::ERR, format, ##__VA_ARGS__)

#if LOG_WARN_ENABLED == 1
#define LOG_WARN(format, ...) TextureGenEngine::Logger::Log(TextureGenEngine::Logger::Level::WARN, format, ##__VA_ARGS__)
#else
#define LOG_WARN(format, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define LOG_INFO(format, ...) TextureGenEngine::Logger::Log(TextureGenEngine::Logger::Level::INFO, format, ##__VA_ARGS__)
#else
#define LOG_INFO(format, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define LOG_DEBUG(format, ...) TextureGenEngine::Logger::Log(TextureGenEngine::Logger::Level::DEBUG, format, ##__VA_ARGS__)
#else
#define LOG_DEBUG(format, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define LOG_TRACE(format, ...) TextureGenEngine::Logger::Log(TextureGenEngine::Logger::Level::TRACE, format, ##__VA_ARGS__)
#else
#define LOG_TRACE(format, ...)
#endif

	};
}