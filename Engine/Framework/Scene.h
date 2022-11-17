#ifndef _SCENE_H
#define _SCENE_H

#include "Actor.h"
#include "Resource/Resource.h"

#include <list>
#include <memory>

namespace en
{
	class Actor;
	class Renderer;

	class Scene : public GameObject, public Serializable, public Resource
	{
	public:
		Scene() = default;
		Scene(const Scene& other) {}
		~Scene() = default;

		CLONE(Scene)

		void Init() override;
		bool Create(std::string name, ...) override;
		void Update() override;
		void Shutdown();
		void PreRender(Renderer& renderer);
		void Render(Renderer& renderer);

		// Inheritance
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void addActor(std::unique_ptr<Actor> actor, bool back = true);
		void Remove() {}

		template<typename T = Actor>
		inline T* getActor()
		{
			for (auto& actor : _actors)
			{
				T* a = dynamic_cast<T*>(actor.get());
				if (a) return a;
			}

			return nullptr;
		}

		template<typename T = Actor>
		inline T* getActor(const std::string& name)
		{
			for (auto& actor : _actors)
			{
				T* a = dynamic_cast<T*>(actor.get());
				if (a->_name == name)
				{
					return a;
				}
				else
				{
					continue;
				}
			}

			return nullptr;
		}

		template<typename T = Actor>
		inline std::vector<T*> getActors(const std::string& tag)
		{
			std::vector<T*> actors;

			for (auto& actor : _actors)
			{
				T* a = dynamic_cast<T*>(actor.get());
				if (a->_tag == tag)
				{
					actors.push_back(a);
				}
				else
				{
					continue;
				}
			}

			return actors;
		}

	private:
		std::list<std::unique_ptr<Actor>> _actors;

	};
}

#endif // _SCENE_H