#ifndef _LOGGER_H
#define _LOGGER_H

#ifdef _DEBUG
#define LOG(format, ...) en::__logger.Log(format, __VA_ARGS__)
#else
#define LOG(format, ...) ((void)0)
#endif // _DEBUG

namespace en
{
	class Logger
	{
	public:
		Logger() = default;
		~Logger() = default;

		void Log(const char* format, ...);

	private:


	};

	extern Logger __logger;
}

#endif // _LOGGER_H