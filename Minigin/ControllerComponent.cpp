#include "MiniginPCH.h"
#include "ControllerComponent.h"

#include "GameTime.h"
#include "GameObject.h"
#include "InputManager.h"
#include "RigidbodyComponent.h"
#include "AnimationComponent.h"

OatmealEngine::ControllerComponent::ControllerComponent(float speedH, float speedV, float jumpForce)
	: m_SpeedHorizontal{speedH}
	, m_SpeedVertical{speedV}
	, m_JumpForce{jumpForce}
{}

void OatmealEngine::ControllerComponent::Awake()
{
	auto& inputManager{InputManager::GetInstance()};
	inputManager.AddInputAction(InputAction("MoveUp", InputTriggerState::Down, SDLK_w, GamepadButton::DPAD_UP));
	inputManager.AddInputAction(InputAction("MoveLeft", InputTriggerState::Down, SDLK_a, GamepadButton::DPAD_LEFT));
	inputManager.AddInputAction(InputAction("MoveDown", InputTriggerState::Down, SDLK_s, GamepadButton::DPAD_DOWN));
	inputManager.AddInputAction(InputAction("MoveRight", InputTriggerState::Down, SDLK_d, GamepadButton::DPAD_RIGHT));
	inputManager.AddInputAction(InputAction("Jump", InputTriggerState::Pressed, SDLK_SPACE, GamepadButton::A));
}

void OatmealEngine::ControllerComponent::Start()
{
	m_pRigidbodyComponent = GetGameObject().lock()->GetComponent<RigidbodyComponent>();
	m_pAnimationComponent = GetGameObject().lock()->GetComponent<AnimationComponent>();
}

void OatmealEngine::ControllerComponent::Update()
{
	UpdateMovement();
}

void OatmealEngine::ControllerComponent::UpdateMovement() const
{
	auto& transform{GetTransform()};
	auto pRigidbody{m_pRigidbodyComponent.lock()};
	auto pAnimaion{m_pAnimationComponent.lock()};
	auto& inputManager{InputManager::GetInstance()};

	bool doingSomething{false};

	if (inputManager.IsActionTriggered("MoveUp"))
	{
		transform.Translate(0.f, -m_SpeedVertical * GameTime::GetInstance().DeltaTime());
		doingSomething = true;
	}
	if (inputManager.IsActionTriggered("MoveLeft"))
	{
		pAnimaion->Play("Move");
		transform.Translate(-m_SpeedHorizontal * GameTime::GetInstance().DeltaTime(), 0.f);
		if (transform.GetScale().x > 0)
			transform.InvertXScale();
		doingSomething = true;
	}
	if (inputManager.IsActionTriggered("MoveDown"))
	{
		transform.Translate(0.f, m_SpeedVertical * GameTime::GetInstance().DeltaTime());
		doingSomething = true;
	}
	if (inputManager.IsActionTriggered("MoveRight"))
	{
		pAnimaion->Play("Move");
		transform.Translate(m_SpeedHorizontal * GameTime::GetInstance().DeltaTime(), 0.f);
		if (transform.GetScale().x < 0)
			transform.InvertXScale();
		doingSomething = true;
	}
	if (inputManager.IsActionTriggered("Jump") && pRigidbody->IsGrounded())
	{
		pRigidbody->AddForce({0, -m_JumpForce});
		pRigidbody->SetGrounded(false);
		doingSomething = true;
	}
	
	if (!doingSomething)
		pAnimaion->Play("Idle");

}
