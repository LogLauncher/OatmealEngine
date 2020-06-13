#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class RigidbodyComponent;
	class AnimationComponent;

	class ControllerComponent final : public BaseComponent
	{
	public:	
		explicit ControllerComponent(float speedH = 100.f, float speedV = 100.f, float jumpForce = 250.f);
		virtual ~ControllerComponent() = default;

		virtual void Awake() override;
		virtual void Update() override;
		virtual void Start() override;

	private:
		float m_SpeedHorizontal;
		float m_SpeedVertical;
		float m_JumpForce;
		
		std::weak_ptr<RigidbodyComponent> m_pRigidbodyComponent; 
		std::weak_ptr<AnimationComponent> m_pAnimationComponent;

		void UpdateMovement() const;

	};
}

