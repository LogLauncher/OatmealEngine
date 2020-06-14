#pragma once
#include "BaseComponent.h"

#include "RigidbodyComponent.h"
#include "AnimationComponent.h"
#include "InputManager.h"

class PlayerComponent final : public OatmealEngine::BaseComponent
{
public:
	enum class State
	{
		MOVING,
		HIT,
		INVULNERABLE,
	};
	explicit PlayerComponent(OatmealEngine::PlayerIndex playerNr);
	virtual ~PlayerComponent() = default;
	DEL_ROF(PlayerComponent);

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;

	virtual void OnCollide(std::shared_ptr<OatmealEngine::BaseCollider> pOther) override;

private:
	OatmealEngine::PlayerIndex m_PlayerNr;

	float m_SpeedH;
	float m_JumpForce;

	const float m_ShootInterval;
	float m_TimerShoot;

	const float m_InvincibilityTime;
	float m_TimerInvincibility;

	std::weak_ptr<OatmealEngine::RigidbodyComponent> m_pRigidbodyComponent;
	std::weak_ptr<OatmealEngine::AnimationComponent> m_pAnimationComponent;

	void UpdateMovement() const;
	void UpdateShoot();

	void ShootBubble();

	State m_State;


};

