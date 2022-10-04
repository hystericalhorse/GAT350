#ifndef _COMPONENT_CHARACTER_H
#define _COMPONENT_CHARACTER_H

#include "Framework/Component.h"
#include "Framework/Event.h"
#include "Physics/Collidable.h"

namespace en
{
	class CharacterComponent : public Component, public Collidable, public Notified
	{
	public:
		CharacterComponent() = default;
		virtual ~CharacterComponent();

		virtual void Init() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void OnCollisionBegin(Actor* other) override {}
		virtual void OnCollisionEnd(Actor* other) override {}

		virtual void onNotification(const Event& event) override {}

	public:
		float _health = 100;
		float _damage = 10;
		float _speed = 0;
	};
}

#endif // _COMPONENT_CHARACTER_H