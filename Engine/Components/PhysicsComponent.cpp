#include "PhysicsComponent.h"
#include "Engine.h"

namespace en
{
	void PhysicsComponent::Force(const Vector2& force)
	{
		_acceleration += force;
	}

	void PhysicsComponent::Update()
	{
		_velocity += _acceleration * __time.ci_time;
		_owner->_Transform().position += _velocity * __time.ci_time;

		_velocity *= _damping;

		_acceleration = Vector2::zero;
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		float& damping = _damping;

		READ_DATA(value, damping);

		return true;
	}
}