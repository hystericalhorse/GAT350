#include "ContactListener.h"

#include "Components/CollisionComponent.h"
#include "Framework/Actor.h"

namespace en
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();

		if (fixA->GetUserData().pointer && fixB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixB->GetUserData().pointer);

			if (!actorA->isAlive() || !actorB->isAlive()) return;
			
			if (actorA->getComponent<en::CollisionComponent>())
			{
				actorA->getComponent<en::CollisionComponent>()->OnCollisionBegin(actorB);
			}

			if (actorB->getComponent<en::CollisionComponent>())
			{
				actorB->getComponent<en::CollisionComponent>()->OnCollisionBegin(actorA);
			}
		}

	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();

		if (fixA->GetUserData().pointer && fixB->GetUserData().pointer)
		{
			Actor* actorA = (Actor*)(fixA->GetUserData().pointer);
			Actor* actorB = (Actor*)(fixB->GetUserData().pointer);

			if (!actorA->isAlive() || !actorB->isAlive()) return;

			if (actorA->getComponent<en::CollisionComponent>())
			{
				actorA->getComponent<en::CollisionComponent>()->OnCollisionEnd(actorB);
			}

			if (actorB->getComponent<en::CollisionComponent>())
			{
				actorB->getComponent<en::CollisionComponent>()->OnCollisionEnd(actorA);
			}
		}
	}
}