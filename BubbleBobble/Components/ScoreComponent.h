#pragma once
#include "BaseComponent.h"

class ScoreComponent final : public OatmealEngine::BaseComponent
{
public:
	explicit ScoreComponent();
	virtual ~ScoreComponent() = default;
	DEL_ROF(ScoreComponent);

	virtual void Update() override;

private:
	const float m_LifeTime;
	float m_Timer;

};

