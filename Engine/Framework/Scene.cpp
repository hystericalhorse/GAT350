#include "Scene.h"
#include "Factory.h"
#include "Renderer/Renderer.h"
#include "Core/Logger.h"

#include <iostream>

namespace en
{
	void Scene::Init()
	{
		for (auto& actor : _actors) { actor->Init(); }
	}

	void Scene::Update()
	{
		auto iter = _actors.begin();
		while (iter != _actors.end())
		{
			(*iter)->Update();
			if (!(*iter)->_living) iter = _actors.erase(iter);
			else iter++;
		}
	}

	void Scene::Shutdown()
	{
		for (auto& actor : _actors)
		{
			actor->toggleActive(false);
			actor->Destroy();
		}

		_actors.clear();
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : _actors)
		{
			actor->Draw(renderer);
		}
	}

	bool Scene::Write(const rapidjson::Value& value) const
	{


		return true;
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			LOG("ERROR: Could not find 'actors' component in level file.");
			return false;
		}

		for (auto& aut : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(aut, type);

			auto actor = Factory::Instance().Retrieve<en::Actor>(type);
			if (!actor)
			{
				LOG("ERROR: Did not find type 'Actor' in actor object.");
				return false;
			}

			actor->Read(aut);

			bool prototype = false;
			READ_DATA(aut, prototype);
			if (prototype)
			{
				std::string name = actor->getName();
				Factory::Instance().Register(name, std::move(actor));
			}
			else
			{
				addActor(std::move(actor));
			}
		}

		return true;
	}

	void Scene::addActor(std::unique_ptr<Actor> actor, bool back)
	{
		actor->_scene = this;
		(back) ? _actors.push_back(std::move(actor)) : _actors.push_front(std::move(actor));
	}
}