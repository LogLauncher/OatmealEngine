#include "MiniginPCH.h"
#include "BubbleComponent.h"

#include "GameObject.h"
#include "GameTime.h"
#include "Utils.h"

using namespace OatmealEngine;

BubbleComponent::BubbleComponent(int directionX)
	: m_TimeMoveSide{.5f}
	, m_TimeMoveUp{2.f}
	, m_TimerMove{0}
	, m_SpeedH{300.f}
	, m_SpeedV{75.f}
	, m_DirectionX{directionX}
	, m_State{State::MOVING_H}
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
		m_State = State::MOVING_H;
	}
	else if (m_TimerMove < (m_TimeMoveSide + m_TimeMoveUp))
	{
		m_pAnimationComponent.lock()->Play("Idle");
		GetTransform().Translate(0.f, m_SpeedV * -1 * dt, 0.f);
		m_State = State::MOVING_U;
	}
	else
	{
		if (m_State != State::POPING)
		{
			m_pAnimationComponent.lock()->Play("Pop", false);
			m_State = State::POPING;
		}
		if (!m_pAnimationComponent.lock()->IsPlayingAnimation() && m_State == State::POPING)
			GetGameObject().lock()->Delete();
	}
}

void BubbleComponent::OnTrigger(std::shared_ptr<BaseCollider> pOther)
{
	const auto& pOtherGameObject{pOther->GetGameObject().lock()};

	if (pOtherGameObject->CompareTag("SolidBlock"))
	{
		if (m_TimerMove < m_TimeMoveSide && m_State == State::MOVING_H)
			m_TimerMove = m_TimeMoveSide;

	}
}
