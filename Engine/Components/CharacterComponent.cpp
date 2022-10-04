#include "CharacterComponent.h"
#include "Engine.h"

namespace en
{
	CharacterComponent::~CharacterComponent()
	{
		__eventmanager.Unsubscribe("EVENT_DAMAGE", _owner);
	}

	void CharacterComponent::Init()
	{
		__eventmanager.Subscribe("EVENT_DAMAGE", std::bind(&CharacterComponent::onNotification, this, std::placeholders::_1), _owner);

		auto component = _owner->getComponent<CollisionComponent>();
		if (component)
		{
			component->setCollisionEnter(std::bind(&CharacterComponent::OnCollisionBegin, this, std::placeholders::_1));
			component->setCollisionExit(std::bind(&CharacterComponent::OnCollisionEnd, this, std::placeholders::_1));
		}
	}

	bool CharacterComponent::Write(const rapidjson::Value& value) const
	{
		// TODO

		return true;
	}

	bool CharacterComponent::Read(const rapidjson::Value& value)
	{
		float& health = _health;
		float& damage = _damage;
		float& speed = _speed;

		READ_DATA(value, health);
		READ_DATA(value, damage);
		READ_DATA(value, speed);

		return true;
	}
}