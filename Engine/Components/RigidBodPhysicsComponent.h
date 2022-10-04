#ifndef _COMPONENT_RIGID_BODY_PHYSICS
#define _COMPONENT_RIGID_BODY_PHYSICS

#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace en
{
	class RigidBodPhysicsComponent : public PhysicsComponent
	{
	public:
		RigidBodPhysicsComponent() = default;
		~RigidBodPhysicsComponent();

		CLONE(RigidBodPhysicsComponent)

		void Init() override;
		void Update() override;

		bool Write(const rapidjson::Value& value) const override;
		bool Read(const rapidjson::Value& value) override;

		void Force(const Vector2& direction) override;

		friend class CollisionComponent;
	public:
		PhysicsSystem::RigidBodyDat data;
		b2Body* _body = nullptr;

	};
}

#endif // _COMPONENT_RIGID_BODY_PHYSICS