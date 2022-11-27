#include "Scene.h"
#include "Factory.h"
#include "Renderer/Renderer.h"
#include "Core/Logger.h"

#include "Engine.h"

#include <iostream>

namespace en
{
	void Scene::Init()
	{
		for (auto& actor : _actors) { actor->Init(); }
	}

	bool Scene::Create(std::string name, ...)
	{
		rapidjson::Document document;
		bool success = en::json::Load(name, document);
		if (!success)
		{
			LOG("Error loading scene %s.", name.c_str());
			return false;
		}
		
		Read(document);
		Init();
		
		return true;
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

	void Scene::PreRender(Renderer& renderer)
	{
		CameraComponent* camera = nullptr;
		for (auto& actor : _actors)
		{
			if (!actor->isActive()) continue;

			auto component = actor->getComponent<en::CameraComponent>();
			if (component)
			{
				camera = component;
				break;
			}
		}

		std::vector<LightComponent*> lights;
		for (auto& actor : _actors)
		{
			if (!actor->isActive()) continue;

			auto component = actor->getComponent<en::LightComponent>();
			if (component)
			{
				lights.push_back(component);
			}
		}

		auto programs = __registry.Get<en::Program>();
		for (auto& program : programs)
		{
			camera->setProgram(program);

			int index = 0;
			for (auto light : lights)
			{
				light->setProgram(program, index++);
			}

			program->setUniform("light_count", index);
			program->setUniform("ambient_color", __renderer.ambient_color);
		}
	}

	void Scene::Render(Renderer& renderer)
	{
		auto camera = getActor("Camera");
		if (camera)
		{
			__renderer.setView(camera->getComponent<en::CameraComponent>()->getView());
			__renderer.setProjection(camera->getComponent<en::CameraComponent>()->getProjection());
		}

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
		READ_NAME_DATA(value, "clear_color", __renderer.clear_color);
		READ_NAME_DATA(value, "ambient_color", __renderer.ambient_color);

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