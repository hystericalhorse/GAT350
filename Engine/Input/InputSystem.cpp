#include "InputSystem.h"
#include <iostream>
#include <SDL.h>

namespace en
{
	const uint32_t key_space	= SDL_SCANCODE_SPACE;
	const uint32_t key_up		= SDL_SCANCODE_UP;
	const uint32_t key_down		= SDL_SCANCODE_DOWN;
	const uint32_t key_left		= SDL_SCANCODE_LEFT;
	const uint32_t key_right	= SDL_SCANCODE_RIGHT;
	const uint32_t key_escape	= SDL_SCANCODE_ESCAPE;

	const uint32_t btn_left		= 0;
	const uint32_t btn_middle	= 1;
	const uint32_t btn_right	= 2;

	void InputSystem::Init()
	{
		const uint8_t* keyboard = SDL_GetKeyboardState(&_numkeys);
		keyboardstate.resize(_numkeys);

		std::copy(keyboard, (keyboard + _numkeys), keyboardstate.begin());

		prev_keyboardstate = keyboardstate;
	}

	void InputSystem::Shutdown()
	{}

	void InputSystem::Update()
	{
		// update SDL
		SDL_Event event;
		SDL_PollEvent(&event);

		// save previous keyboard state
		prev_keyboardstate = keyboardstate;

		// get present keyboard state
		const uint8_t* keyboard = SDL_GetKeyboardState(nullptr);
		std::copy(keyboard, (keyboard + _numkeys), keyboardstate.begin());

		// std::cout << (bool)keyboardstate[SDL_SCANCODE_SPACE] << std::endl;

		//save previous mouse state
		prev_mousebtnstate = mousebtnstate;

		// get present mouse state
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		_mousepos = en::Vector2(x, y);
		mousebtnstate[0] = buttons & SDL_BUTTON_LMASK;
		mousebtnstate[1] = buttons & SDL_BUTTON_MMASK;
		mousebtnstate[2] = buttons & SDL_BUTTON_RMASK;
	}

	InputSystem::KeyState InputSystem::getKeyState(uint32_t key)
	{
		KeyState state = InputSystem::KeyState::IDLE;

		if (getKeyDown(key) && !getPrevKeyDown(key))
		{
			state = InputSystem::KeyState::PRESSED;
		}
		if (getKeyDown(key) && getPrevKeyDown(key))
		{
			state = InputSystem::KeyState::HELD;
		}
		if (!getKeyDown(key) && getPrevKeyDown(key))
		{
			state = InputSystem::KeyState::RELEASED;
		}
		
		return state;
	}

	bool InputSystem::keyIdle(uint32_t key)
	{
		if (getKeyState(key) == InputSystem::KeyState::IDLE)
			return true;
		else
			return false;
	}
	bool InputSystem::keyPressed(uint32_t key)
	{
		if (getKeyState(key) == InputSystem::KeyState::PRESSED)
			return true;
		else
			return false;
	}
	bool InputSystem::keyHeld(uint32_t key)
	{
		if (getKeyState(key) == InputSystem::KeyState::HELD)
			return true;
		else
			return false;
	}
	bool InputSystem::keyReleased(uint32_t key)
	{
		if (getKeyState(key) == InputSystem::KeyState::RELEASED)
			return true;
		else
			return false;
	}

	InputSystem::KeyState InputSystem::getButtonState(uint32_t button)
	{
		KeyState state = InputSystem::KeyState::IDLE;

		if (getButtonDown(button) && !getPrevButtonDown(button))
		{
			state = InputSystem::KeyState::PRESSED;
		}
		if (getButtonDown(button) && getPrevButtonDown(button))
		{
			state = InputSystem::KeyState::HELD;
		}
		if (!getButtonDown(button) && getPrevButtonDown(button))
		{
			state = InputSystem::KeyState::RELEASED;
		}

		return state;
	}
}