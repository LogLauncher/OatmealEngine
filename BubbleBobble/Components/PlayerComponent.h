#pragma once
#include "BaseComponent.h"

#include "RigidbodyComponent.h"
#include "AnimationComponent.h"

class PlayerComponent final : public OatmealEngine::BaseComponent
{
public:
	explicit PlayerComponent(int playerNr);
	virtual ~PlayerComponent() = default;
	DEL_ROF(PlayerComponent);

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;


private:
	int m_PlayerNr;

	float m_SpeedH;
	float m_JumpForce;

	std::weak_ptr<OatmealEngine::RigidbodyComponent> m_pRigidbodyComponent;
	std::weak_ptr<OatmealEngine::AnimationComponent> m_pAnimationComponent;

};

