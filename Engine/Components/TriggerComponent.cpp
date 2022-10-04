#include "TriggerComponent.h"

#include "Engine.h"

namespace en
{
	void TriggerComponent::Init()
	{
		
	}

	void TriggerComponent::Update()
	{

	}

	bool TriggerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool TriggerComponent::Read(const rapidjson::Value& value)
	{
		if (value.HasMember("event") && value["event"].IsArray())
		{
			for (auto& ev : value["event"].GetArray())
			{
				std::string& name = _event->name;
				READ_DATA(value, name);

				std::string data_type;
				READ_DATA(value, data_type);

				if (data_type == "int")
				{
					int& data = std::get<int>(_event->data);
					READ_DATA(value, data);
				}
				else if (data_type == "bool")
				{
					bool& data = std::get<bool>(_event->data);
					READ_DATA(value, data);
				}
				else if (data_type == "float")
				{
					float& data = std::get<float>(_event->data);
					READ_DATA(value, data);
				}
				else if (data_type == "string")
				{
					std::string& data = std::get<std::string>(_event->data);
					READ_DATA(value, data);
				}
				else
				{
					LOG("ERROR: Event data must be an integer, boolean, float, or string.");
				}

				std::string reciever;
				READ_DATA(value, reciever);
				Actor* actor = _owner->_scene->getActor(reciever);

				if (actor)
				{
					_event->reciever = _owner->_scene->getActor(reciever);
				}
				else
				{
					LOG("ERROR: Could not find intentended reciever %s", reciever);
				}
			}

			return true;
		}

		return false;
	}

	void TriggerComponent::flagTriggered()
	{

	}

	void TriggerComponent::OnCollisionBegin(Actor* other)
	{
		en::__eventmanager.Notify(*_event);
	}

	void TriggerComponent::OnCollisionEnd(Actor* other)
	{

	}
}