#include "MiniginPCH.h"
#include "ZenChanEnemyComponent.h"

#include "GameObject.h"
#include "GameTime.h"

using namespace OatmealEngine;

ZenChanEnemyComponent::ZenChanEnemyComponent()
	: EnemyComponent(150.f, 35.f, 450.f)
	, m_State{State::MOVING}
	, m_TimeTillPop{5.f}
	, m_Timer{0}
{}

void ZenChanEnemyComponent::Update()
{
	const float dt{GameTime::GetInstance().DeltaTime()};
	switch (m_State)
	{
	case State::MOVING:
		break;
	case State::HIT:
		m_Timer += dt;
		if (m_Timer >= m_TimeTillPop)
		{
			m_pAnimationComponent.lock()->Play("Move");
			m_Timer = 0;
			m_State = State::MOVING;
			m_pRigidbodyComponent.lock()->EnableGravity(true);
		}
		GetTransform().Translate(0.f, -m_SpeedV * dt);
		break;
	}
}

void ZenChanEnemyComponent::OnCollide(std::shared_ptr<BaseCollider> pOther)
{
	auto pOtherGameObject{pOther->GetGameObject().lock()};
	if (pOtherGameObject->CompareTag("Bubble") && m_State == State::MOVING)
	{
		m_pAnimationComponent.lock()->Play("Hit");
		m_State = State::HIT;
		m_pRigidbodyComponent.lock()->EnableGravity(false);
		pOtherGameObject->Delete();
	}
}
