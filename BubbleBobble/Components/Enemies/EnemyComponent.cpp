#include "MiniginPCH.h"
#include "EnemyComponent.h"

#include "GameObject.h"

EnemyComponent::EnemyComponent(float speedH, float speedV, float jumpForce)
	: m_SpeedH{speedH}
	, m_SpeedV{speedV}
	, m_JumpForce{jumpForce}
{}

void EnemyComponent::Start()
{
	m_pRigidbodyComponent = GetGameObject().lock()->GetComponent<OatmealEngine::RigidbodyComponent>();
	m_pAnimationComponent = GetGameObject().lock()->GetComponent<OatmealEngine::AnimationComponent>();
}
