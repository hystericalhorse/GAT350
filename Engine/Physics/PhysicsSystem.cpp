#include "PhysicsSystem.h"
#include "Math/MathUtils.h"

namespace en
{
	const float PhysicsSystem::pixelsPerUnit = 48.0f;
	
	void PhysicsSystem::Init()
	{
		b2Vec2 gravity{ 0.0f, 9.82f };
		_world = std::make_unique<b2World>(gravity);
		_contactlistener = std::make_unique<en::ContactListener>();
		_world->SetContactListener(_contactlistener.get());
	}

	void PhysicsSystem::Shutdown()
	{
		// TODO
	}

	void PhysicsSystem::Update()
	{
		_world->Step( 1.0f / 60.0f, 8, 3);
	}

	b2Body* PhysicsSystem::CreateBody(const Vector2& position, float angle, const PhysicsSystem::RigidBodyDat& data)
	{
		Vector2 worldPos = ScreenToWorld(position);

		b2BodyDef bodyDef;
		bodyDef.type = (data.is_dynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = *((b2Vec2*)(&worldPos));
		bodyDef.angle = en::radians(angle);
		bodyDef.fixedRotation = data.constrain_rotation;
		b2Body* body = _world->CreateBody(&bodyDef);

		return body;
	}

	void PhysicsSystem::DestroyBody(b2Body* body)
	{
		_world->DestroyBody(body);
	}

	void PhysicsSystem::SetCollisionBox(b2Body* body, const CollisionDat& data, class Actor* actor)
	{
		b2PolygonShape shape;
		Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size * 0.5f);
		shape.SetAsBox(worldSize.x, worldSize.y);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.is_trigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);

		body->CreateFixture(&fixtureDef);
	}

	void PhysicsSystem::SetStaticCollisionBox(b2Body* body, const CollisionDat& data, class Actor* actor)
	{
		Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size * 0.5f);

		b2Vec2 vs[4] =
		{
			{ -worldSize.x, -worldSize.y },
			{  worldSize.x, -worldSize.y },
			{  worldSize.x,  worldSize.y },
			{ -worldSize.x,  worldSize.y },
		};

		b2ChainShape shape;
		shape.CreateLoop(vs, 4);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.is_trigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);

		body->CreateFixture(&fixtureDef);
	}
}
