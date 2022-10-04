#ifndef _TIME_H
#define _TIME_H

#include <chrono>

namespace en
{
	class Time
	{
	public:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = long long;

		float ci_time = 0;
		float time = 0;

	public:
		Time() :
			_starttimepoint{ clock::now() },
			_frametimepoint{clock::now()}
		{}
		~Time() = default;

		void Tick();
		void reset()
		{
			_starttimepoint = clock::now();
		}

	private:
		clock::time_point _starttimepoint; // time point at start of application
		clock::time_point _frametimepoint; // time point at start of each frame

	};
}

#endif // _TIME_H