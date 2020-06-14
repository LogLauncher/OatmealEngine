#pragma once
#include "BaseComponent.h"

#include "AnimationComponent.h"
#include "BaseCollider.h"

class BubbleComponent : public OatmealEngine::BaseComponent
{
public:
	enum class State
	{
		MOVING_H,
		MOVING_U,
		POPING
	};

	explicit BubbleComponent(int directionX);
	virtual ~BubbleComponent() = default;
	DEL_ROF(BubbleComponent);

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnTrigger(std::shared_ptr<OatmealEngine::BaseCollider> pOther) override;

private:
	std::weak_ptr<OatmealEngine::AnimationComponent> m_pAnimationComponent;

	const float m_TimeMoveSide;
	const float m_TimeMoveUp;
	float m_TimerMove;

	const float m_SpeedH;
	const float m_SpeedV;
	int m_DirectionX;

	State m_State;

};

