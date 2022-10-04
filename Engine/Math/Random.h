#ifndef _RANDOM_H
#define _RANDOM_H

#include <random>

namespace en
{
	inline void seedRand(int seed)
	{
		srand(seed);
	}

	inline int random()
	{
		return rand();
	}

	inline int random(int max)
	{
		return (random() % max);
	}

	inline int random(int max, int min)
	{
		return (min + random() % ((max - min) + 1));
	}

	inline float randomf()
	{
		return (rand() / (float) RAND_MAX);
	}

	inline float randomf(float max)
	{
		return (randomf() * max);
	}

	inline float randomf(float max, float min)
	{
		return (min + randomf(max - min));
	}
}

#endif // _RANDOM_H