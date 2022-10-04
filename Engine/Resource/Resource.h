#ifndef _RESOURCE_H
#define _RESOURCE_H

#include <string>
#include <cstdarg>

namespace en
{
	class Resource
	{
	public:
		Resource() = default;
		~Resource() = default;

		virtual bool Create(std::string name, ...) = 0;

	private:


	};
}

#endif // _RESOURCE_H