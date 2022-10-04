#include "RigidBodPhysicsComponent.h"
#include "Engine.h"

namespace en
{
	RigidBodPhysicsComponent::~RigidBodPhysicsComponent()
	{
		if (_body) __physics.DestroyBody(_body);
	}

	void RigidBodPhysicsComponent::Init()
	{
		_body = __physics.CreateBody(_owner->_Transform().position, _owner->_Transform().rotation, data);
		_body->SetGravityScale(data.gravity_scale);
		_body->SetLinearDamping(_damping);
	}

	void RigidBodPhysicsComponent::Force(const Vector2& force)
	{
		_body->ApplyForceToCenter(VECTOR2_TO_B2VEC2(force), true);
	}

	void RigidBodPhysicsComponent::Update()
	{
		Vector2 position = B2VEC2_TO_VECTOR2(_body->GetPosition());
		_owner->_Transform().position = PhysicsSystem::WorldToScreen(position);
		_owner->_Transform().rotation = en::degrees(_body->GetAngle());

		_velocity = B2VEC2_TO_VECTOR2(_body->GetLinearVelocity());
	}

	bool RigidBodPhysicsComponent::Write(const rapidjson::Value& value) const
	{
		// TODO

		return true;
	}

	bool RigidBodPhysicsComponent::Read(const rapidjson::Value& value)
	{
		PhysicsComponent::Read(value);

		float& gravity_scale = data.gravity_scale;
		bool& constrain_rotation = data.constrain_rotation;
		bool& is_dynamic = data.is_dynamic;

		READ_DATA(value, gravity_scale);
		READ_DATA(value, constrain_rotation);
		READ_DATA(value, is_dynamic);

		return true;
	}

}