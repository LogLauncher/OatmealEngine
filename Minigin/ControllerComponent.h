#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class ControllerComponent final : public BaseComponent
	{
	public:	
		explicit ControllerComponent(float speedH = 100.f, float speedV = 100.f);
		virtual ~ControllerComponent() = default;

		virtual void Awake() override;
		virtual void Update() override;

	private:
		float m_SpeedHorizontal;
		float m_SpeedVertical;
		
		void UpdateMovement() const;

	};
}

