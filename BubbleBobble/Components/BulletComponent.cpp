#include "MiniginPCH.h"
#include "BulletComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "Utils.h"

using namespace OatmealEngine;

BulletComponent::BulletComponent(int directionX)
	: m_TimeMoveSide{.5f}
	, m_TimeMoveUp{1.f}
	, m_TimerMove{0}
	, m_Speed{300.f}
	, m_DirectionX{directionX}
{}

void BulletComponent::Start()
{
	m_pAnimationComponent = GetGameObject().lock()->GetComponent<AnimationComponent>();
}

void BulletComponent::Update()
{
	const float dt{GameTime::GetInstance().DeltaTime()};

	m_TimerMove += dt;
	if (m_TimerMove < m_TimeMoveSide)
	{
		m_pAnimationComponent.lock()->Play("Idle");
		GetTransform().Translate(m_Speed * m_DirectionX * dt, 0.f);
	}
	else if (m_TimerMove < (m_TimeMoveSide + m_TimeMoveUp))
	{
		m_pAnimationComponent.lock()->Play("Idle");
		GetTransform().Translate(0.f, m_Speed * -1 * dt, 0.f);
	}
	else
		m_pAnimationComponent.lock()->Play("Pop", false);
}

void BulletComponent::OnTrigger(std::shared_ptr<BaseCollider> pOther)
{
	std::cout << "Bullet collided" << std::endl;
}
