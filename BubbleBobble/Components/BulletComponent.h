#pragma once
#include "BaseComponent.h"

#include "AnimationComponent.h"
#include "BaseCollider.h"

class BulletComponent : public OatmealEngine::BaseComponent
{
public:
	explicit BulletComponent(int directionX);
	virtual ~BulletComponent() = default;
	DEL_ROF(BulletComponent);

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnTrigger(std::shared_ptr<OatmealEngine::BaseCollider> pOther) override;

private:
	std::weak_ptr<OatmealEngine::AnimationComponent> m_pAnimationComponent;

	const float m_TimeMoveSide;
	const float m_TimeMoveUp;
	float m_TimerMove;

	const float m_Speed;
	int m_DirectionX;

};

