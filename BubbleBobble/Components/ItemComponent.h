#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "BaseCollider.h"

class ItemComponent final : public OatmealEngine::BaseComponent
{
public:
	explicit ItemComponent(const std::weak_ptr<OatmealEngine::Texture2D>& texturePoints, int points, int animationStartRow, int animationStartCol);
	virtual ~ItemComponent() = default;
	DEL_ROF(ItemComponent);

	virtual void Update() override;

	virtual void OnCollide(std::shared_ptr<OatmealEngine::BaseCollider> pOther) override;

private:
	std::weak_ptr<OatmealEngine::Texture2D> m_pTexturePoints;
	const int m_Points;
	const int m_StartRow;
	const int m_StartCol;

	const float m_TimerBeforePickup;
	const float m_TimeBeforeDelete;
	float m_Timer;

	bool m_CanPickUp;

};

