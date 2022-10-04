#ifndef _FACTORY_H
#define _FACTORY_H

#include "Singleton.h"
#include "Core/Logger.h"

#include <memory>
#include <string>
#include <map>

namespace en
{
	class GameObject;

	class FactoryFloor // Base Class
	{
	public:
		virtual ~FactoryFloor() = default;

		virtual std::unique_ptr<GameObject> Create() = 0;
	};

	template <typename T>
	class Creator : public FactoryFloor
	{
	public:
		std::unique_ptr<GameObject> Create() override
		{
			return std::make_unique<T>();
		}
	};

	template <typename T>
	class Prototype : public FactoryFloor
	{
	public:
		~Prototype() = default;
		Prototype(std::unique_ptr<T> instance) : _instance{ std::move(instance) } {}

		std::unique_ptr<GameObject> Create() override
		{
			return _instance->Clone();
		}

	private:
		std::unique_ptr<T> _instance;
	};

	class Factory : public Singleton<Factory>
	{
	public:
		void Shutdown()
		{
			_fregist.clear();
		}

		template <typename T>
		void Register(const std::string& key)
		{
			_fregist[key] = std::make_unique<Creator<T>>();
		}

		template <typename T>
		void Register(const std::string& key, std::unique_ptr<T> instance)
		{
			_fregist[key] = std::make_unique<Prototype<T>>(std::move(instance));
		}

		template <typename T>
		std::unique_ptr<T> Retrieve(const std::string& key)
		{
			auto iter = (_fregist.find(key));
			if (iter != _fregist.end())
			{
				return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
			}

			LOG("ERROR: Could not find key %s", key.c_str());
			return nullptr;
		}

	private:
		std::map<std::string, std::unique_ptr<FactoryFloor>> _fregist;

	};
}

#endif // _FACTORY_H