#ifndef _INPUT_SYSTEM_H
#define _INPUT_SYSTEM_H
#include "Math/Vector2.h"
#include "Math/MathUtils.h"
#include <cstdint>
#include <vector>
#include <array>

struct SDL_GetKeyboardState;

namespace en
{
	class InputSystem
	{
	public:
		enum class KeyState
		{
			IDLE,
			PRESSED,
			HELD,
			RELEASED
		};

	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Init();
		void Shutdown();

		void Update();
		
		KeyState getKeyState(uint32_t key);
		bool getKeyDown(uint32_t key) { return keyboardstate[key]; }
		bool getPrevKeyDown(uint32_t key) { return prev_keyboardstate[key]; }

		const glm::vec2& getMousePos() const { return _mousepos; }
		const glm::vec2& getMouseRelative() const { return _mouserelative; }
		const glm::vec2& getMousePrev() const { return _prev_mousepos; }

		KeyState getButtonState(uint32_t button);
		bool getButtonDown(uint32_t button) { return mousebtnstate[button]; }
		bool getPrevButtonDown(uint32_t button) { return prev_mousebtnstate[button]; }

		bool keyIdle(uint32_t key);
		bool keyPressed(uint32_t key);
		bool keyHeld(uint32_t key);
		bool keyReleased(uint32_t key);

	private:
		int _numkeys = 0;

		std::vector<uint8_t> keyboardstate
		{};
		std::vector<uint8_t> prev_keyboardstate
		{};

		glm::vec2 _mousepos {0, 0};
		glm::vec2 _prev_mousepos;
		glm::vec2 _mouserelative;

		std::array<uint8_t, 3> mousebtnstate{};
		std::array<uint8_t, 3> prev_mousebtnstate{};
	};

	extern const uint32_t key_space;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_escape;

	extern const uint32_t key_lctrl;
	extern const uint32_t key_lshift;

	extern const uint32_t key_w;
	extern const uint32_t key_a;
	extern const uint32_t key_s;
	extern const uint32_t key_d;

	extern const uint32_t btn_left;
	extern const uint32_t btn_right;
	extern const uint32_t btn_middle;
}

#endif // _INPUT_SYSTEM_H