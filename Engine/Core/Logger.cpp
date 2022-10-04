#include "Logger.h"
#include <cstdarg>
#include <iostream>

namespace en
{
	Logger __logger;

	void Logger::Log(const char* format, ...)
	{
		va_list args;
		va_start(args, format);

		char str[256];
		vsprintf_s(str, 256, format, args);

		std::cout << str << std::endl;
		
		va_end(args);
	}
}