#include "Actor.h"
#include "Engine.h"

namespace en
{
	Actor::Actor(const Actor& other)
	{
		this->_name = other._name;
		this->_tag = other._tag;
		this->_transform = other._transform;
		this->_lifespan = other._lifespan;

		this->_scene = other._scene;
		if (other._parent) this->_parent = other._parent;

		for (auto& component : other._components)
		{
			auto clone = std::unique_ptr<en::Component>( (Component*) component->Clone().release() );
			addComponent(std::move(clone));
		}
	}

	Actor::~Actor()
	{
		for (auto& component : _components)
		{
			component.reset();
		}

		if (_parent != nullptr) delete _parent;
	}
	 
	void Actor::Init()
	{
		for (auto& component : _components)
		{
			component->Init();
		}

		for (auto& child : _children)
		{
			child->Init();
		}
	}

	void Actor::Update()
	{
		if (!_active)
		{
			if (_destroyOnInactive)
			{
				this->Destroy();
			}

			return;
		}

		if (_lifespan != 0.0)
		{
			_lifespan -= en::__time.ci_time;
			if (_lifespan <= 0) this->Destroy();
		}

		for (auto& component : _components)
		{
			component->Update();
		}

		for (auto& child : _children)
		{
			child->Update();
		}

		if (_parent) _transform.update(_parent->_transform.matrix);
		else _transform.update();
	}

	void Actor::addComponent(std::unique_ptr<Component> component)
	{
		component->_owner = this;
		_components.push_back(std::move(component));
	}
	void Actor::addChild(std::unique_ptr<Actor> child)
	{
		child->_parent = this;
		_children.push_back(std::move(child));
	}

	bool Actor::Write(const rapidjson::Value& value) const
	{


		return true;
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		std::string& name = _name;
		std::string& tag = _tag;
		bool& active = _active;
		bool& destroy_on_inactive = _destroyOnInactive;
		float& lifespan = _lifespan;

		READ_DATA(value, name);
		READ_DATA(value, tag);
		READ_DATA(value, active);
		READ_DATA(value, destroy_on_inactive);
		READ_DATA(value, lifespan);

		if (value.HasMember("transform")) _transform.Read(value["transform"]);

		if (value.HasMember("components") && value["components"].IsArray())
		{
			for (auto& aut : value["components"].GetArray())
			{
				std::string type;
				READ_DATA(aut, type);

				auto component = Factory::Instance().Retrieve<en::Component>(type);
				if (!component->Read(aut))
				{
					LOG("ERROR: Problem reading component data.");
				}
				addComponent(std::move(component));
			}
		}

		return true;
	}

	
	void Actor::Draw(Renderer& renderer)
	{
		if (!_active) return;

		for (auto& component : _components)
		{
			auto r = dynamic_cast<RenderComponent*>(component.get());
			if (r)
			{
				r->Draw(renderer);
			}
		}

		for (auto& child : _children)
		{
			child.get()->Draw(renderer);
		}
	}
}

