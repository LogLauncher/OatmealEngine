#include "MiniginPCH.h"
#include "EnemyComponent.h"

#include "GameTime.h"
#include "GameObject.h"

using namespace OatmealEngine;

EnemyComponent::EnemyComponent(float speedH, float speedV, float jumpForce, float attackInterval)
	: m_State{State::MOVING}
	, m_SpeedH{speedH}
	, m_SpeedV{speedV}
	, m_JumpForce{jumpForce}
	, m_AttackInterval{attackInterval}
	, m_TimerAttack{0}
	, m_CanAttack{false}
{}

void EnemyComponent::Start()
{
	m_pRigidbodyComponent = GetGameObject().lock()->GetComponent<OatmealEngine::RigidbodyComponent>();
	m_pAnimationComponent = GetGameObject().lock()->GetComponent<OatmealEngine::AnimationComponent>();
}

void EnemyComponent::Update()
{
	m_TimerAttack += GameTime::GetInstance().DeltaTime();
	if (m_TimerAttack >= m_AttackInterval)
		m_CanAttack = true;

	// Check position if under the level
	auto& transform{GetTransform()};
	const auto& pos{transform.GetPosition()};
	const auto& scale{transform.GetScale()};
	const int windowHeight{GameSettings::WindowSettings.Height};

	if (pos.y > windowHeight)
		transform.Translate(0, int(-windowHeight - 16 * scale.y));
	if (pos.y < (-16 * scale.y))
	{
		transform.SetPosition(pos.x, 0.f);
		m_pRigidbodyComponent.lock()->SetVelocity({0,0});
		return;
	}

}
