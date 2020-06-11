#pragma once
#include "Singleton.h"

#include <XInput.h>
#include <map>

#include "SDL_keycode.h"

namespace OatmealEngine
{
	enum class InputTriggerState
	{
		Pressed,
		Released,
		Down
	};

	enum GamepadButton
	{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,

		BACK = XINPUT_GAMEPAD_BACK,
		START = XINPUT_GAMEPAD_START,

		LEFT_SHOLDER = XINPUT_GAMEPAD_LEFT_SHOULDER,
		LEFT_TRIGGER = 0x0400,	// XINPUT_GAMEPAD_LEFT_TRIGGER
		RIGHT_SHOLDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		RIGHT_TRIGGER = 0x0800,	// XINPUT_GAMEPAD_RIGHT_TRIGGER

		DPAD_UP = XINPUT_GAMEPAD_DPAD_UP,
		DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,
		DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
		DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,

		LEFT_THUMB_CLICK = XINPUT_GAMEPAD_LEFT_THUMB,
		RIGHT_THUMB_CLICK = XINPUT_GAMEPAD_RIGHT_THUMB,

		INVALID = 0xA000,

	};

	struct InputAction
	{
		InputAction() :
			ActionID(""),
			TriggerState(InputTriggerState::Pressed),
			KeyboardCode(-1),
			GamepadButtonCode(GamepadButton::INVALID),
			IsTriggered(false) {}

		InputAction(const std::string& actionID, InputTriggerState triggerState = InputTriggerState::Pressed, SDL_Keycode keyboardCode = -1, GamepadButton gamepadButtonCode = GamepadButton::INVALID) :
			ActionID(actionID),
			TriggerState(triggerState),
			KeyboardCode(keyboardCode),
			GamepadButtonCode(gamepadButtonCode),
			IsTriggered(false) {}

		const std::string ActionID;
		InputTriggerState TriggerState;
		SDL_Keycode KeyboardCode;
		GamepadButton GamepadButtonCode;
		bool IsTriggered;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool Update();
		bool AddInputAction(InputAction action);
		bool IsActionTriggered(const std::string& actionID);

	private:
		XINPUT_STATE m_OldGamepadState{};
		XINPUT_STATE m_CurrentGamepadState{};
		std::map<std::string, InputAction> m_InputActions;

		bool IsGamepadButtonDown(GamepadButton button, bool previousFrame = false);
		bool IsKeyboardKeyDown(const std::vector<std::pair<SDL_Keycode, InputTriggerState>>& keyState, InputAction& currentAction);

	};

}
