#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "Resource.h"

#include <map>
#include <string>
#include <memory>

namespace en
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		void Init();
		void Shutdown();

		template <typename T, typename ... T_args>
		inline std::shared_ptr<T> Get(std::string key, T_args... args)
		{
			if (_resources.find(key) != _resources.end())
			{
				return std::dynamic_pointer_cast<T>(_resources[key]);
			}

			std::shared_ptr<T> res = std::make_shared<T>();
			const std::string& name = key;
			res->Create(name, args...);
			_resources[key] = res;

			return res;
		}

	private:
		std::map<std::string, std::shared_ptr<en::Resource>> _resources;

	};
}

#endif // _RESOURCE_MANAGER_H