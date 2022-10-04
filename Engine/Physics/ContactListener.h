#ifndef _CONTACT_LISTENER_H
#define _CONTACT_LISTENER_H

#include "box2d.h"

namespace en
{
	class ContactListener : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;

	};
}

#endif _CONTACT_LISTENER_H