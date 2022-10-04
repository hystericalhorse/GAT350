#ifndef _COMPONENT_PHYSICS_H
#define _COMPONENT_PHYSICS_H

#include "Framework/Component.h"
#include "Math/Vector2.h"

namespace en
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		CLONE(PhysicsComponent)

		virtual void Update() override;
		void Draw(en::Renderer& renderer) {}

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		virtual void Force(const Vector2& force);

	public:
		Vector2 _velocity { 0, 0 };
		Vector2 _acceleration { 0, 0 };

		float _damping = 0.99f;

	};
}

#endif // _COMPONENT_PHYSICS_H