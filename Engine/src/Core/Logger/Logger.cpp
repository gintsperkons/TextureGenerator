#include "Logger.h"
#include "../Asserts.h"

#include <stdio.h>




void TextureGen::Logger::Log(Logger::Level level, const char *format, ...)
{
	const char *levelStr[6] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: " };
	va_list args;
	va_start(args, format);
	printf(levelStr[(int)level]);
	vprintf(format, args);
	va_end(args);
}


void ReportAssertionFailure(const char *expression, const char *file, int line, const char *message)
{
	TextureGen::Logger::Log(TextureGen::Logger::Level::FATAL, "Assertion failed: %s\nFile: %s\nLine: %d\nMessage: %s\n", expression, file, line, message);
}