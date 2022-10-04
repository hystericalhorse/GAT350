#include "CollisionComponent.h"
#include "Engine.h"

namespace en
{
	void CollisionComponent::Init()
	{
		auto component = _owner->getComponent<en::RigidBodPhysicsComponent>();
		if (component)
		{
			if (data.size.x == 0 && data.size.y == 0)
			{
				auto renderComp = _owner->getComponent<en::RenderComponent>();
				if (renderComp) data.size = Vector2 { renderComp->_Source().w, renderComp->_Source().h };
			}

			data.size *= _owner->_Transform().scale * scale_offset;

			if (component->_body->GetType() == b2_staticBody)
			{
				__physics.SetStaticCollisionBox(component->_body, data, _owner);
			}
			else
			{
				__physics.SetCollisionBox(component->_body, data, _owner);
			}
		}
	}

	void CollisionComponent::Update()
	{

	}

	bool CollisionComponent::Write(const rapidjson::Value& value) const
	{


		return true;
	}

	bool CollisionComponent::Read(const rapidjson::Value& value)
	{
		Vector2& size = data.size;
		float& density = data.density;
		float& friction = data.friction;
		float& restitution = data.restitution;
		bool& is_trigger = data.is_trigger;

		READ_DATA(value, size);
		READ_DATA(value, density);
		READ_DATA(value, friction);
		READ_DATA(value, restitution);
		READ_DATA(value, is_trigger);
		READ_DATA(value, scale_offset);

		return true;
	}

	void CollisionComponent::OnCollisionBegin(Actor* other)
	{
		if (!other) return;

		try
		{
			if (_enterFunction) _enterFunction(other);
		}
		catch (...)
		{
			LOG("ERROR: Collision error.");
		}
	}

	void CollisionComponent::OnCollisionEnd(Actor* other)
	{
		if (!other) return;

		// This causes an Access Reading Violation during application closing.
		try
		{
			if (_exitFunction) _exitFunction(other);
		}
		catch (...)
		{
			LOG("ERROR: Collision error.");
		}
		
	}
}