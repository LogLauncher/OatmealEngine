#include "MiniginPCH.h"
#include "InputManager.h"

#include <SDL.h>

void OatmealEngine::InputManager::Initialize()
{
	if (m_IsInitialized)
		return;

	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(i, &state);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
	m_IsInitialized = true;
}

bool OatmealEngine::InputManager::Update()
{
	// Update Gamepad states
	UpdateGamepadStates();

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
				if (!IsGamepadButtonDown(currentAction.GamepadButtonCode, currentAction.PlayerNr, true) && IsGamepadButtonDown(currentAction.GamepadButtonCode, currentAction.PlayerNr))
					currentAction.IsTriggered = true;
			// Keyboard
			if (!currentAction.IsTriggered)
				if (IsKeyboardKeyDown(keyState, currentAction))
					currentAction.IsTriggered = true;
					
			break;
		case InputTriggerState::Down:
			// GamePad
			if (!currentAction.IsTriggered)
				if (IsGamepadButtonDown(currentAction.GamepadButtonCode, currentAction.PlayerNr, true) && IsGamepadButtonDown(currentAction.GamepadButtonCode, currentAction.PlayerNr))
					currentAction.IsTriggered = true;
			// Keyboard
			if (!currentAction.IsTriggered)
				if (keyboardState[SDL_GetScancodeFromKey(currentAction.KeyboardCode)])
					currentAction.IsTriggered = true;
			break;
		case InputTriggerState::Released:
			// GamePad
			if (!currentAction.IsTriggered)
				if (IsGamepadButtonDown(currentAction.GamepadButtonCode, currentAction.PlayerNr, true) && !IsGamepadButtonDown(currentAction.GamepadButtonCode, currentAction.PlayerNr))
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

bool OatmealEngine::InputManager::IsActionTriggered(const std::string& actionID, PlayerIndex playerID)
{
	UINT playerIndex = static_cast<UINT>(playerID);
	return m_InputActions[actionID + std::to_string(playerIndex)].IsTriggered;
}

bool OatmealEngine::InputManager::AddInputAction(InputAction action)
{
	UINT playerIndex = static_cast<UINT>(action.PlayerNr);
	std::string actionId{action.ActionID + std::to_string(playerIndex)};
	auto it{m_InputActions.find(actionId)};
	if (it != m_InputActions.end())
		return false;

	m_InputActions.insert(std::make_pair(actionId, action));

	return true;
}

bool OatmealEngine::InputManager::IsGamepadButtonDown(GamepadButton button, PlayerIndex playerNr, bool previousFrame)
{
	if (button != GamepadButton::INVALID)
	{
		UINT playerIndex = static_cast<UINT>(playerNr);
		if (previousFrame)
		{
			if ((m_OldGamepadState[playerIndex].Gamepad.wButtons & button) != 0)
				return true;
			if (button == GamepadButton::LEFT_TRIGGER && m_OldGamepadState[playerIndex].Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				return true;
			if (button == GamepadButton::RIGHT_TRIGGER && m_OldGamepadState[playerIndex].Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				return true;
		}
		else
		{
			if ((m_CurrentGamepadState[playerIndex].Gamepad.wButtons & button) != 0)
				return true;
			if (button == GamepadButton::LEFT_TRIGGER && m_CurrentGamepadState[playerIndex].Gamepad.bLeftTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
				return true;
			if (button == GamepadButton::RIGHT_TRIGGER && m_CurrentGamepadState[playerIndex].Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
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

void OatmealEngine::InputManager::UpdateGamepadStates()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_ConnectedGamepads[i])
			return;

		m_OldGamepadState[i] = m_CurrentGamepadState[i];

		const DWORD dwResult = XInputGetState(i, &m_CurrentGamepadState[i]);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}
