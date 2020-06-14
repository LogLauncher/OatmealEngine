#include "MiniginPCH.h"
#include "BubbleComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "Utils.h"

using namespace OatmealEngine;

BubbleComponent::BubbleComponent(int directionX)
	: m_TimeMoveSide{.5f}
	, m_TimeMoveUp{3.f}
	, m_TimerMove{0}
	, m_SpeedH{300.f}
	, m_SpeedV{100.f}
	, m_DirectionX{directionX}
	, m_Poping{false}
{}

void BubbleComponent::Start()
{
	m_pAnimationComponent = GetGameObject().lock()->GetComponent<AnimationComponent>();
}

void BubbleComponent::Update()
{
	const float dt{GameTime::GetInstance().DeltaTime()};

	m_TimerMove += dt;
	if (m_TimerMove < m_TimeMoveSide)
	{
		m_pAnimationComponent.lock()->Play("Idle");
		GetTransform().Translate(m_SpeedH * m_DirectionX * dt, 0.f);
	}
	else if (m_TimerMove < (m_TimeMoveSide + m_TimeMoveUp))
	{
		m_pAnimationComponent.lock()->Play("Idle");
		GetTransform().Translate(0.f, m_SpeedV * -1 * dt, 0.f);
	}
	else
	{
		if (!m_Poping)
		{
			m_pAnimationComponent.lock()->Play("Pop", false);
			m_Poping = true;
		}
		if (!m_pAnimationComponent.lock()->IsPlayingAnimation() && m_Poping)
			GetGameObject().lock()->Delete();
	}
}

void BubbleComponent::OnTrigger(std::shared_ptr<BaseCollider> pOther)
{
	std::cout << pOther->GetGameObject().lock()->GetTag() << std::endl;
}
