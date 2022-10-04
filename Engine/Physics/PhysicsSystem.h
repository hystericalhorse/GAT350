#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "Math/Vector2.h"
#include "ContactListener.h"
#include "box2d.h"
#include <memory>

#define VECTOR2_TO_B2VEC2(vec) (*(b2Vec2*)(&vec))
#define B2VEC2_TO_VECTOR2(vec) (*(en::Vector2*)(&vec))

namespace en
{
	class ContactListener;

	class PhysicsSystem
	{
	public:
		struct RigidBodyDat
		{
			float gravity_scale = 1.0;
			bool constrain_rotation = false; // if false will not rotate along z-axis.
			bool is_dynamic = true; // if false, object is static in world.
		};

		struct CollisionDat
		{
			Vector2 size { 0.0f, 0.0f };
			float density = 0.8f;
			float friction = 0.5f;
			float restitution = 0.3f;
			bool is_trigger = false;
		};

	public:
		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void Init();
		void Shutdown();

		void Update();

		b2Body* CreateBody(const Vector2& position, float angle, const RigidBodyDat& data);
		void DestroyBody(b2Body* body);

		void SetCollisionBox(b2Body* body, const CollisionDat& data, class Actor* actor = nullptr);
		void SetStaticCollisionBox(b2Body* body, const CollisionDat& data, class Actor* actor = nullptr);

		static Vector2 ScreenToWorld(const Vector2& screen)
		{
			return screen * (1 / pixelsPerUnit);
		}

		static Vector2 WorldToScreen(const Vector2& world)
		{
			return world * pixelsPerUnit;
		}

	private:
		std::unique_ptr<b2World> _world;
		std::unique_ptr<en::ContactListener> _contactlistener;

		static const float pixelsPerUnit;
	};
}

#endif // _PHYSICS_SYSTEM_H