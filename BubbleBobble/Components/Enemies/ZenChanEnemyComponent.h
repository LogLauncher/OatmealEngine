#pragma once
#include "EnemyComponent.h"
#include "BaseCollider.h"

class ZenChanEnemyComponent final : public EnemyComponent
{
public:
	explicit ZenChanEnemyComponent();
	virtual ~ZenChanEnemyComponent() = default;
	DEL_ROF(ZenChanEnemyComponent);

	virtual void Awake() override;
	virtual void Update() override;
	virtual void OnCollide(std::shared_ptr<OatmealEngine::BaseCollider> pOther) override;

private:
	const float m_TimeTillPop;
	float m_Timer;

	int m_Direction;

};

