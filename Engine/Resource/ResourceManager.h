#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "Resource.h"
#include "Core/Utils.h"

#include <map>
#include <string>
#include <memory>
#include <vector>

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
		std::shared_ptr<T> Get(std::string key, T_args... args);

		template <typename T>
		std::vector<std::shared_ptr<T>> Get();

	private:
		std::map<std::string, std::shared_ptr<en::Resource>> _resources;

	};

	template <typename T, typename ... T_args>
	inline std::shared_ptr<T> ResourceManager::Get(std::string key, T_args... args)
	{
		key = en::Utils::make_lowercase(key);

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

	template <typename T>
	inline std::vector<std::shared_ptr<T>> ResourceManager::Get()
	{
		std::vector<std::shared_ptr<T>> result;

		for (auto& resource : _resources)
		{
			if (dynamic_cast<T*>(resource.second.get()))
			{
				result.push_back(std::dynamic_pointer_cast<T>(resource.second));
			}
		}

		return result;
	}
}

#endif // _RESOURCE_MANAGER_H