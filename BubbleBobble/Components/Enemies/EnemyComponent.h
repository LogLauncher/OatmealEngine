#pragma once
#include "BaseComponent.h"
#include "RigidbodyComponent.h"
#include "AnimationComponent.h"

class EnemyComponent : public OatmealEngine::BaseComponent
{
public:
	enum class State
	{
		MOVING,
		HIT,
	};

	explicit EnemyComponent(float speedH, float speedV, float jumpForce, float attackInterval = 1.f);
	virtual ~EnemyComponent() = default;
	DEL_ROF(EnemyComponent);

	virtual void Start() override;
	virtual void Update() override;

	State GetState() const { return m_State; }
	bool CanAttack() const { return m_CanAttack; }
	void ResetAttack() { m_TimerAttack = 0; }

protected:
	const float m_SpeedH;
	const float m_SpeedV;
	const float m_JumpForce;

	const float m_AttackInterval;
	float m_TimerAttack;

	std::weak_ptr<OatmealEngine::RigidbodyComponent> m_pRigidbodyComponent;
	std::weak_ptr<OatmealEngine::AnimationComponent> m_pAnimationComponent;

	State m_State;
	bool m_CanAttack;

};

