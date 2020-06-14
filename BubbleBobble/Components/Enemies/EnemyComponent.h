#pragma once
#include "BaseComponent.h"
#include "RigidbodyComponent.h"
#include "AnimationComponent.h"

class EnemyComponent : public OatmealEngine::BaseComponent
{
public:
	explicit EnemyComponent(float speedH, float speedV, float jumpForce);
	virtual ~EnemyComponent() = default;
	DEL_ROF(EnemyComponent);

	virtual void Start() override;

protected:
	const float m_SpeedH;
	const float m_SpeedV;
	const float m_JumpForce;

	std::weak_ptr<OatmealEngine::RigidbodyComponent> m_pRigidbodyComponent;
	std::weak_ptr<OatmealEngine::AnimationComponent> m_pAnimationComponent;

};

