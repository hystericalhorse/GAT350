#include "EventManager.h"

namespace en
{
	void EventManager::Init()
	{

	}

	void EventManager::Shutdown()
	{

	}

	void EventManager::Update()
	{

	}

	void EventManager::Subscribe(const std::string& eventname, Event::eventptr function, GameObject* reciever)
	{
		Observer observer;
		observer.reciever = reciever;
		observer.function = function;

		_events[eventname].push_back(observer);
	}

	void EventManager::Unsubscribe(const std::string& eventname, GameObject* reciever)
	{
		auto& observers = _events[eventname];

		for (auto iter = observers.begin(); iter != observers.end(); iter++)
		{
			if (iter->reciever == reciever)
			{
				observers.erase(iter);
				break;
			}
		}
	}

	void EventManager::Notify(const Event& event)
	{
		auto& observers = _events[event.name];

		for (auto& observer : observers)
		{
			if (!event.reciever)
			{
				observer.function(event);
			}
		}
	}
}