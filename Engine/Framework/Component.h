#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "GameObject.h"
#include "Serialization/Serializable.h"
#include "Actor.h"

namespace en
{
	class Component : public GameObject, public Serializable
	{
	public:
		Component() = default;
		Component(const Component& other) {}
		~Component() = default;

		virtual void Init() override {}
		
		virtual bool Write(const rapidjson::Value& value) const = 0;
		virtual bool Read(const rapidjson::Value& value) = 0;
		
		virtual void Update() = 0;

		friend class Actor;
	protected:
		Actor* _owner = nullptr;

	};
}

#endif // _COMPONENT_H