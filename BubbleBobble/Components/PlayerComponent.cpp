#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "GameTime.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "GameSettings.h"

PlayerComponent::PlayerComponent(OatmealEngine::PlayerIndex playerNr)
	: m_PlayerNr{playerNr}
	, m_SpeedH{250.f}
	, m_JumpForce{470.f}
{}

void PlayerComponent::Awake()
{
	auto& inputManager{OatmealEngine::InputManager::GetInstance()};
	switch (m_PlayerNr)
	{
	case OatmealEngine::PlayerIndex::PlayerOne:
		inputManager.AddInputAction(OatmealEngine::InputAction("MoveLeft", OatmealEngine::InputTriggerState::Down, SDLK_LEFT, OatmealEngine::GamepadButton::DPAD_LEFT, OatmealEngine::PlayerIndex::PlayerOne));
		inputManager.AddInputAction(OatmealEngine::InputAction("MoveRight", OatmealEngine::InputTriggerState::Down, SDLK_RIGHT, OatmealEngine::GamepadButton::DPAD_RIGHT, OatmealEngine::PlayerIndex::PlayerOne));
		inputManager.AddInputAction(OatmealEngine::InputAction("Jump", OatmealEngine::InputTriggerState::Pressed, SDLK_UP, OatmealEngine::GamepadButton::DPAD_UP, OatmealEngine::PlayerIndex::PlayerOne));
		inputManager.AddInputAction(OatmealEngine::InputAction("Shoot", OatmealEngine::InputTriggerState::Pressed, SDLK_RCTRL, OatmealEngine::GamepadButton::A, OatmealEngine::PlayerIndex::PlayerOne));
		break;
	case OatmealEngine::PlayerIndex::PlayerTwo:
		inputManager.AddInputAction(OatmealEngine::InputAction("MoveLeft", OatmealEngine::InputTriggerState::Down, SDLK_a, OatmealEngine::GamepadButton::DPAD_LEFT, OatmealEngine::PlayerIndex::PlayerTwo));
		inputManager.AddInputAction(OatmealEngine::InputAction("MoveRight", OatmealEngine::InputTriggerState::Down, SDLK_d, OatmealEngine::GamepadButton::DPAD_RIGHT, OatmealEngine::PlayerIndex::PlayerTwo));
		inputManager.AddInputAction(OatmealEngine::InputAction("Jump", OatmealEngine::InputTriggerState::Pressed, SDLK_w, OatmealEngine::GamepadButton::DPAD_UP, OatmealEngine::PlayerIndex::PlayerTwo));
		inputManager.AddInputAction(OatmealEngine::InputAction("Shoot", OatmealEngine::InputTriggerState::Pressed, SDLK_LCTRL, OatmealEngine::GamepadButton::A, OatmealEngine::PlayerIndex::PlayerTwo));
		break;
	default:
		break;
	}

}

void PlayerComponent::Start()
{
	m_pRigidbodyComponent = GetGameObject().lock()->GetComponent<OatmealEngine::RigidbodyComponent>();
	m_pAnimationComponent = GetGameObject().lock()->GetComponent<OatmealEngine::AnimationComponent>();
}

void PlayerComponent::Update()
{
	UpdateMovement();

	// Check position if under the level
	auto& transform{GetTransform()};
	const auto& pos{transform.GetPosition()};
	const auto& scale{transform.GetScale()};
	const int windowHeight{OatmealEngine::GameSettings::WindowSettings.Height};

	if (pos.y > windowHeight)
		transform.Translate(0, int(-windowHeight - 16 * scale.y));
	if (pos.y < (-16 * scale.y))
		transform.Translate(0, windowHeight);
}

void PlayerComponent::UpdateMovement()
{
	auto& transform{GetTransform()};
	auto pRigidbody{m_pRigidbodyComponent.lock()};
	auto pAnimaion{m_pAnimationComponent.lock()};
	auto& inputManager{OatmealEngine::InputManager::GetInstance()};

	UINT playerIndex = static_cast<UINT>(m_PlayerNr);
	bool doingSomething{false};
	if (inputManager.IsActionTriggered("MoveLeft" + std::to_string(playerIndex)))
	{
		pAnimaion->Play("Move");
		transform.Translate(-m_SpeedH * OatmealEngine::GameTime::GetInstance().DeltaTime(), 0.f);
		if (transform.GetScale().x > 0)
			transform.InvertXScale();
		doingSomething = true;
	}
	if (inputManager.IsActionTriggered("MoveRight" + std::to_string(playerIndex)))
	{
		pAnimaion->Play("Move");
		transform.Translate(m_SpeedH * OatmealEngine::GameTime::GetInstance().DeltaTime(), 0.f);
		if (transform.GetScale().x < 0)
			transform.InvertXScale();
		doingSomething = true;
	}
	if (inputManager.IsActionTriggered("Jump" + std::to_string(playerIndex)) && pRigidbody->IsGrounded())
	{
		pRigidbody->AddForce({0, -m_JumpForce});
		pRigidbody->SetGrounded(false);
		doingSomething = true;
	}

	if (!doingSomething)
		pAnimaion->Play("Idle");
}
