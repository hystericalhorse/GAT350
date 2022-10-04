#ifndef _SINGLETON_H
#define _SINGLETON_H

namespace en
{
	template<class T>
	class Singleton
	{
	public:
		Singleton(const Singleton&) = delete;

		Singleton& operator = (const Singleton&) = delete;

		static T& Instance()
		{
			static T instance;
			return instance;
		}

	public:
		Singleton() = default;
	};
}

#endif// _SINGLETON_H