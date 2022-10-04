#ifndef _COMPONENT_TRIGGER_H
#define _COMPONENT_TRIGGER_H

#include "Framework/Component.h"
#include "Physics/Collidable.h"
#include "Framework/EventManager.h"

namespace en
{
	class TriggerComponent : public Component, public Collidable
	{
	public:
		TriggerComponent() = default;

		void Init() override;
		void Update() override;

		bool Write(const rapidjson::Value& value) const override;
		bool Read(const rapidjson::Value& value) override;

		void OnCollisionBegin(Actor* other) override;
		void OnCollisionEnd(Actor* other) override;

		void flagTriggered();

		void toggleTriggerable() { (_triggered) ? _triggered = false : _triggered = true; }
		void toggleTriggerable(bool t) { _triggered = t; }

	public:
		en::Event* _event = nullptr;
		bool _triggered = false;

	};
}

#endif // _COMPONENT_TRIGGER_H