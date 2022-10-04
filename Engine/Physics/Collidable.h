#ifndef _INTERFACE_COLLIDABLE_H
#define _INTERFACE_COLLIDABLE_H

namespace en
{
	class Actor;

	class Collidable
	{
	public:
		virtual void OnCollisionBegin(Actor* other) = 0;
		virtual void OnCollisionEnd(Actor* other) = 0;

	};
}

#endif // _INTERFACE_COLLIDABLE_H