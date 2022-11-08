#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

#include "Event.h"
#include <string>
#include <map>
#include <list>

namespace en
{
	class EventManager
	{
	public:
		struct Observer
		{
			GameObject* reciever;

			Event::eventptr function;
		};


	public:
		void Init();
		void Shutdown();
		void Update();

		void Subscribe(const std::string& eventname, Event::eventptr function, GameObject* reciever = nullptr);
		void Unsubscribe(const std::string& eventname, GameObject* reciever);

		void Notify(const Event& event);

	private:
		std::map<std::string, std::list<Observer>> _events;
	};
}

#endif // _EVENT_MANAGER_H