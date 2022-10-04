#ifndef _ACTOR_H
#define _ACTOR_H

#include "GameObject.h"
#include "Component.h"

#include <vector>
#include <memory>

namespace en
{
	class Scene;
	class Renderer;
	class Component;

	class Actor : public GameObject, public Serializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		~Actor();

		CLONE(Actor)

		void Init() override;
		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		// Inheritance
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void addComponent(std::unique_ptr<Component> component);
		void addChild(std::unique_ptr<Actor> child);

		Scene* getScene() { return _scene; }

		virtual void OnCollision(Actor* other) {}

		void Destroy() { _living = false; }
		bool isAlive() { bool a;  (_living) ? a = true : a = false; return a; }
		void toggleActive() { (_active) ? _active = false : _active = true; }
		void toggleActive(bool b) { _active = b; }
		bool isActive() { return _active; }

		Transform& _Transform() { return this->_transform; }
		const std::string& getName() { return _name; }
		void setName(const std::string& string) { this->_name = string; }
		const std::string& getTag() { return _tag; }
		void setTag(const std::string& string) { this->_tag = string; }

		float& _Lifespan() { return _lifespan; }

		template<typename T>
		inline T* getComponent()
		{
			for (auto& component : _components)
			{
				T* a = dynamic_cast<T*>(component.get());
				if (a) return a;
			}

			return nullptr;
		}
		
		friend class Scene;
	public:
		bool _active = true;
		bool _destroyOnInactive = false;
		bool _living = true;
		float _lifespan = 0.0f;
		std::string _name = "";
		std::string _tag = "";

		Transform _transform;

		Scene* _scene = nullptr;
		Actor* _parent = nullptr;

		std::vector<std::unique_ptr<Component>> _components;
		std::vector<std::unique_ptr<Actor>> _children;
	};
}

#endif // _ACTOR_H