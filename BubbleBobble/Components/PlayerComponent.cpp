#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "GameTime.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "GameSettings.h"
#include "../Systems/Prefabs.h"
#include "Enemies/ZenChanEnemyComponent.h"

using namespace OatmealEngine;

PlayerComponent::PlayerComponent(PlayerIndex playerNr)
	: m_PlayerNr{playerNr}
	, m_SpeedH{250.f}
	, m_JumpForce{450.f}
	, m_ShootInterval{.35f}
	, m_TimerShoot{0}
	, m_State{State::MOVING}
	, m_InvincibilityTime{1.f}
	, m_TimerInvincibility{0}
{}

void PlayerComponent::Awake()
{
	auto& inputManager{InputManager::GetInstance()};
	switch (m_PlayerNr)
	{
	case PlayerIndex::PlayerOne:
		inputManager.AddInputAction(InputAction("MoveLeft", InputTriggerState::Down, SDLK_LEFT, GamepadButton::DPAD_LEFT, PlayerIndex::PlayerOne));
		inputManager.AddInputAction(InputAction("MoveRight", InputTriggerState::Down, SDLK_RIGHT, GamepadButton::DPAD_RIGHT, PlayerIndex::PlayerOne));
		inputManager.AddInputAction(InputAction("Jump", InputTriggerState::Pressed, SDLK_UP, GamepadButton::A, PlayerIndex::PlayerOne));
		inputManager.AddInputAction(InputAction("Shoot", InputTriggerState::Pressed, SDLK_RCTRL, GamepadButton::B, PlayerIndex::PlayerOne));
		break;
	case PlayerIndex::PlayerTwo:
		inputManager.AddInputAction(InputAction("MoveLeft", InputTriggerState::Down, SDLK_a, GamepadButton::DPAD_LEFT, PlayerIndex::PlayerTwo));
		inputManager.AddInputAction(InputAction("MoveRight", InputTriggerState::Down, SDLK_d, GamepadButton::DPAD_RIGHT, PlayerIndex::PlayerTwo));
		inputManager.AddInputAction(InputAction("Jump", InputTriggerState::Pressed, SDLK_w, GamepadButton::A, PlayerIndex::PlayerTwo));
		inputManager.AddInputAction(InputAction("Shoot", InputTriggerState::Pressed, SDLK_LCTRL, GamepadButton::B, PlayerIndex::PlayerTwo));
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
	// Check position if under the level
	auto& transform{GetTransform()};
	const auto& pos{transform.GetPosition()};
	const auto& scale{transform.GetScale()};
	const int windowHeight{GameSettings::WindowSettings.Height};

	if (pos.y > windowHeight)
		transform.Translate(0, int(-windowHeight - 16 * scale.y));
	if (pos.y < (-16 * scale.y))
	{
		m_pRigidbodyComponent.lock()->ResetVelocityX();
		return;
	}

	switch (m_State)
	{
	case PlayerComponent::State::MOVING:
		UpdateMovement();
		UpdateShoot();
		break;
	case PlayerComponent::State::HIT:
		if (!m_pAnimationComponent.lock()->IsPlayingAnimation())
			m_State = State::INVULNERABLE;
		break;
	case PlayerComponent::State::INVULNERABLE:
		m_TimerInvincibility += GameTime::GetInstance().DeltaTime();
		if (m_TimerInvincibility >= m_InvincibilityTime)
		{
			m_TimerInvincibility = 0;
			m_State = State::MOVING;
		}
		UpdateMovement();
		UpdateShoot();
		break;
	}

}

void PlayerComponent::UpdateMovement() const
{
	auto& transform{GetTransform()};
	auto pRigidbody{m_pRigidbodyComponent.lock()};
	auto pAnimaion{m_pAnimationComponent.lock()};
	auto& inputManager{InputManager::GetInstance()};

	UINT playerIndex = static_cast<UINT>(m_PlayerNr);
	bool doingSomething{false};
	if (inputManager.IsActionTriggered("MoveLeft" + std::to_string(playerIndex)))
	{
		pAnimaion->Play("Move");
		transform.Translate(-m_SpeedH * GameTime::GetInstance().DeltaTime(), 0.f);
		if (transform.GetScale().x > 0)
			transform.InvertXScale();
		doingSomething = true;
	}
	if (inputManager.IsActionTriggered("MoveRight" + std::to_string(playerIndex)))
	{
		pAnimaion->Play("Move");
		transform.Translate(m_SpeedH * GameTime::GetInstance().DeltaTime(), 0.f);
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
void PlayerComponent::UpdateShoot()
{
	m_TimerShoot += GameTime::GetInstance().DeltaTime();
	if (m_TimerShoot >= m_ShootInterval)
	{
		UINT playerIndex = static_cast<UINT>(m_PlayerNr);
		if (InputManager::GetInstance().IsActionTriggered("Shoot" + std::to_string(playerIndex)))
		{
			m_pAnimationComponent.lock()->Play("Shoot", false);
			ShootBubble();
			m_TimerShoot = 0;
		}
	}
}

void PlayerComponent::ShootBubble()
{
	const auto& pos{GetTransform().GetPosition()};
	const int directionX{Sign(GetTransform().GetScale().x)};
	const auto& size{m_pRigidbodyComponent.lock()->GetCollider().lock()->GetSize()};
	const SDL_Point halfSize{int(size.x / 2.f), int(size.y / 2.f)};
	Prefabs::Bubble(glm::vec3{pos.x + (size.x * directionX), pos.y, 0.f}, directionX, int(m_PlayerNr) * 2);
}

void PlayerComponent::OnCollide(std::shared_ptr<BaseCollider> pOther)
{
	const auto& pOtherGameObject{pOther->GetGameObject().lock()};
	if (pOtherGameObject->CompareTag("Enemy") && m_State == State::MOVING)
	{
		auto pEnemy{pOtherGameObject->GetComponent<ZenChanEnemyComponent>().lock()};
		if (pEnemy)
		{
			if (pEnemy->GetState() == EnemyComponent::State::MOVING && pEnemy->CanAttack())
			{
				m_pAnimationComponent.lock()->Play("Hit", false);
				m_State = State::HIT;
				pEnemy->ResetAttack();
			}
		}
	}
}
