#ifndef _COMPONENT_COLLISION_H
#define _COMPONENT_COLLISION_H

#include "Framework/Actor.h"
#include "Framework/Component.h"
#include "Physics/Collidable.h"
#include "Physics/PhysicsSystem.h"

#include <functional>

namespace en
{
	class CollisionComponent : public Component, public Collidable
	{
	public:
		using actorptr = std::function<void(en::Actor*)>;

	public:
		CollisionComponent() = default;

		CLONE(CollisionComponent)

		void Init() override;
		void Update() override;

		bool Write(const rapidjson::Value& value) const override;
		bool Read(const rapidjson::Value& value) override;

		void OnCollisionBegin(Actor* other) override;
		void OnCollisionEnd(Actor* other) override;

		void setCollisionEnter(actorptr function) { _enterFunction = function; }
		void setCollisionExit(actorptr function) { _exitFunction = function; }

		friend class Actor;
	public:
		PhysicsSystem::CollisionDat data;
		Vector2 scale_offset { 0.5f, 0.5f };

		actorptr _enterFunction;
		actorptr _exitFunction;

	};
}

#endif // _COMPONENT_COLLISION_H