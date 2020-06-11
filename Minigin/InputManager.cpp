#include "MiniginPCH.h"
#include "InputManager.h"

#include <SDL.h>

bool OatmealEngine::InputManager::Update()
{
	// Update Gamepad states
	m_OldGamepadState = m_CurrentGamepadState;
	ZeroMemory(&m_CurrentGamepadState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentGamepadState);

	// Update keyboard
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

	std::vector<std::pair<SDL_Keycode, InputTriggerState>> keyState{};

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			keyState.emplace_back(e.key.keysym.sym, InputTriggerState::Pressed);
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
			keyState.emplace_back(e.key.keysym.sym, InputTriggerState::Released);
	}

	for (auto& actionPair : m_InputActions)
	{
		auto& currentAction{actionPair.second};
		currentAction.IsTriggered = false;

		switch (currentAction.TriggerState)
		{
		case InputTriggerState::Pressed:
			// GamePad
			if (!currentAction.IsTriggered)
				if (!IsGamepadButtonDown(currentAction.GamepadButtonCode, true) && IsGamepadButtonDown(currentAction.GamepadButtonCode))
					currentAction.IsTriggered = true;
			// Keyboard
			if (!currentAction.IsTriggered)
				if (IsKeyboardKeyDown(keyState, currentAction))
					currentAction.IsTriggered = true;
					
			break;
		case InputTriggerState::Down:
			// GamePad
			if (!currentAction.IsTriggered)
				if (IsGamepadButtonDown(currentAction.GamepadButtonCode, true) && IsGamepadButtonDown(currentAction.GamepadButtonCode))
					currentAction.IsTriggered = true;
			// Keyboard
			if (!currentAction.IsTriggered)
				if (keyboardState[SDL_GetScancodeFromKey(currentAction.KeyboardCode)])
					currentAction.IsTriggered = true;
			break;
		case InputTriggerState::Released:
			// GamePad
			if (!currentAction.IsTriggered)
				if (IsGamepadButtonDown(currentAction.GamepadButtonCode, true) && !IsGamepadButtonDown(currentAction.GamepadButtonCode))
					currentAction.IsTriggered = true;
			// Keyboard
			if (!currentAction.IsTriggered)
				if (IsKeyboardKeyDown(keyState, currentAction))
					currentAction.IsTriggered = true;
			break;
		}
	}

	return true;
}

bool OatmealEngine::InputManager::IsActionTriggered(const std::string& actionID)
{
	return m_InputActions[actionID].IsTriggered;
}
bool OatmealEngine::InputManager::AddInputAction(InputAction action)
{
	auto it{m_InputActions.find(action.ActionID)};
	if (it != m_InputActions.end())
		return false;

	m_InputActions.insert(std::make_pair(action.ActionID, action));

	return true;
}

bool OatmealEngine::InputManager::IsGamepadButtonDown(GamepadButton button, bool previousFrame)
{
	if (button != GamepadButton::INVALID)
	{
		if (previousFrame)
		{
			if ((m_OldGamepadState.Gamepad.wButtons & button) != 0)
				return true;
			if (button == GamepadButton::LEFT_TRIGGER && m_OldGamepadState.Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				return true;
			if (button == GamepadButton::RIGHT_TRIGGER && m_OldGamepadState.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				return true;
		}
		else
		{
			if ((m_CurrentGamepadState.Gamepad.wButtons & button) != 0)
				return true;
			if (button == GamepadButton::LEFT_TRIGGER && m_CurrentGamepadState.Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				return true;
			if (button == GamepadButton::RIGHT_TRIGGER && m_CurrentGamepadState.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				return true;
		}
	}
		
	return false;
}
bool OatmealEngine::InputManager::IsKeyboardKeyDown(const std::vector<std::pair<SDL_Keycode, InputTriggerState>>& keyState, InputAction& currentAction)
{
	for (auto& key : keyState)
	{
		if (key.second != currentAction.TriggerState)
			continue;

		if (currentAction.KeyboardCode == key.first)
			return true;
	}
	return false;
}

