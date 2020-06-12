#include "MiniginPCH.h"
#include "ControllerComponent.h"

#include "InputManager.h"
#include "GameTime.h"

OatmealEngine::ControllerComponent::ControllerComponent(float speedH, float speedV)
	: m_SpeedHorizontal{speedH}
	, m_SpeedVertical{speedV}
{}

void OatmealEngine::ControllerComponent::Awake()
{
	auto& inputManager{InputManager::GetInstance()};
	inputManager.AddInputAction(InputAction("MoveUp", InputTriggerState::Down, SDLK_w, GamepadButton::DPAD_UP));
	inputManager.AddInputAction(InputAction("MoveLeft", InputTriggerState::Down, SDLK_a, GamepadButton::DPAD_LEFT));
	inputManager.AddInputAction(InputAction("MoveDown", InputTriggerState::Down, SDLK_s, GamepadButton::DPAD_DOWN));
	inputManager.AddInputAction(InputAction("MoveRight", InputTriggerState::Down, SDLK_d, GamepadButton::DPAD_RIGHT));
}

void OatmealEngine::ControllerComponent::Update()
{
	UpdateMovement();
}

void OatmealEngine::ControllerComponent::UpdateMovement() const
{
	auto& inputManager{InputManager::GetInstance()};
	if (inputManager.IsActionTriggered("MoveUp"))
		GetTransform().Translate(0.f, -m_SpeedVertical * GameTime::GetInstance().DeltaTime());
	if (inputManager.IsActionTriggered("MoveLeft"))
		GetTransform().Translate(-m_SpeedHorizontal * GameTime::GetInstance().DeltaTime(), 0.f);
	if (inputManager.IsActionTriggered("MoveDown"))
		GetTransform().Translate(0.f, m_SpeedVertical * GameTime::GetInstance().DeltaTime());
	if (inputManager.IsActionTriggered("MoveRight"))
		GetTransform().Translate(m_SpeedHorizontal * GameTime::GetInstance().DeltaTime(), 0.f);
}
