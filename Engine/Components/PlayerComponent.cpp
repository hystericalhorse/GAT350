#include "PlayerComponent.h"

#include "CollisionComponent.h"
#include "Engine.h"

#include <functional>
#include <iostream>

namespace en
{
	PlayerComponent::~PlayerComponent()
	{
		CharacterComponent::~CharacterComponent();
	}

	void PlayerComponent::Init()
	{
		CharacterComponent::Init();
		_gametime = 10.0;
	}
	
	void PlayerComponent::Update()
	{
		_gametime -= en::__time.ci_time;
		if (_gametime <= 0)
		{
			
			_owner->getComponent<en::SpriteAnimComponent>()->_sequence = &(_owner->getComponent<en::SpriteAnimComponent>()->_sequences["blinking"]);
			if (!blinking) 
			{
				_gametime = en::__time.ci_time * 12;
				blinking = true;
			}
			else
			{
				_owner->getComponent<en::SpriteAnimComponent>()->_sequence = &(_owner->getComponent<en::SpriteAnimComponent>()->_sequences["idle"]);
				_gametime = en::randomf(4.0, 20.0);
				blinking = false;
			}
		}

		if (_groundcount > 0) _jumpcount = 0;

		auto physics = (_owner->getComponent<en::PhysicsComponent>());

		float modi = (_groundcount > 0) ? 1 : 0.2f;

		if (en::__inputsys.getKeyDown(en::key_left))
		{
			_direction = en::Vector2::left;
			if (physics) physics->Force(Vector2::left * _speed * modi);
		}

		if (en::__inputsys.getKeyDown(en::key_right))
		{
			_direction = en::Vector2::right;
			if (physics) physics->Force(Vector2::right * _speed * modi);
		}

		if (en::__inputsys.getKeyState(en::key_up) == en::InputSystem::KeyState::PRESSED)
		{
			if (_groundcount >= 0)
			{
				if (_jumpcount == 0)
				{
					_direction = en::Vector2::up;
					if (physics) physics->Force(Vector2::up * _jump_multiplier * 100);
					_jumpcount++;
				}
			}
			
		}

		auto camera = _owner->getScene()->getActor("Camera");
		if (camera)
		{
			camera->_Transform().position = en::lerp(camera->_Transform().position, _owner->_Transform().position, 1.0);
		}

		auto anim = (_owner->getComponent<en::SpriteAnimComponent>());
		if (anim)
		{
			if (std::fabs(_direction.x) > 0)
			{
				anim->setSequence("running");
			}
		}
	}

	void PlayerComponent::OnCollisionBegin(Actor* other)
	{
		if (other->getTag() == "Pickup")
		{
			Event event;
			event.name = "EVT_EXAMPLE";
			event.data = 1;

			en::__eventmanager.Notify(event);

			other->getComponent<en::AudioComponent>()->Play();
			other->Destroy();
		}

		if (other->getTag() == "Ground")
		{
			_groundcount++;
		}
	}

	void PlayerComponent::OnCollisionEnd(Actor* other)
	{
		if (other->getTag() == "Ground")
		{
			_groundcount--;
		}
	}

	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		
		float& jump_multiplier = _jump_multiplier;
		READ_DATA(value, jump_multiplier);

		return true;
	}

	void PlayerComponent::onNotification(const Event& event)
	{
		if (event.name == "EVENT_DAMAGE")
		{
			_health -= std::get<float>(event.data);
		}
	}
}
