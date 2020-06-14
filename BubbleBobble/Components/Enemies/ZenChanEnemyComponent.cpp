#include "MiniginPCH.h"
#include "ZenChanEnemyComponent.h"

#include "GameTime.h"
#include "GameObject.h"
#include "..\..\Systems\GameManager.h"
#include "ResourceManager.h"
#include "..\..\Systems\Prefabs.h"

using namespace OatmealEngine;

ZenChanEnemyComponent::ZenChanEnemyComponent()
	: EnemyComponent(150.f, 35.f, 450.f)
	, m_TimeTillPop{5.f}
	, m_Timer{0}
	, m_Direction{RandomInt(0,1) ? -1 : 1}
{}

void ZenChanEnemyComponent::Awake()
{
	if (m_Direction < 0)
		GetTransform().InvertXScale();
}

void ZenChanEnemyComponent::Update()
{
	// Call base update
	EnemyComponent::Update();

	const float dt{GameTime::GetInstance().DeltaTime()};
	switch (m_State)
	{
	case State::MOVING:
		m_pAnimationComponent.lock()->Play("Move");

		// Toggle direction
		if (RandomFloat(0, 1) <= 0.00005f)
		{
			m_Direction *= -1;
			GetTransform().InvertXScale();
		}

		// Move
		GetTransform().Translate(m_SpeedH * dt * m_Direction, 0.f);

		// Jump sometimes
		if (RandomFloat(0, 1) <= 0.00001f && m_pRigidbodyComponent.lock()->IsGrounded())
			m_pRigidbodyComponent.lock()->AddForce({0.f,-m_JumpForce});

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
	
	// Bubble check
	if (pOtherGameObject->CompareTag("Bubble") && m_State == State::MOVING)
	{
		m_pAnimationComponent.lock()->Play("Hit");
		m_State = State::HIT;
		m_pRigidbodyComponent.lock()->EnableGravity(false);
		pOtherGameObject->Delete();
	}

	// Check when bumping into walls
	if (pOtherGameObject->CompareTag("SolidBlock") && m_State == State::MOVING)
	{
		const auto& pos{GetTransform().GetPosition()};
		const auto& size{m_pRigidbodyComponent.lock()->GetCollider().lock()->GetSize()};
		const auto& otherPos{pOtherGameObject->GetTransform().GetPosition()};

		if (pos.y + (size.y * 2.f / 3.f) > otherPos.y)
		{
			m_Direction *= -1;
			GetTransform().InvertXScale();
		}
	}

	// Check if player collision
	if (pOtherGameObject->CompareTag("Player") && m_State == State::HIT)
	{
		auto texture{ResourceManager::GetInstance().LoadTexture("Misc")};
		Prefabs::Item(GetTransform().GetPosition(), texture, texture, 100, 2, 0);
		GameManager::GetInstance().RemoveEnemy(GetGameObject());
		GetGameObject().lock()->Delete();
	}

}
