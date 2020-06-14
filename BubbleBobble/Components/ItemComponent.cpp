#include "MiniginPCH.h"
#include "ItemComponent.h"

#include "GameTime.h"
#include "GameObject.h"
#include "../Systems/Prefabs.h"

using namespace OatmealEngine;

ItemComponent::ItemComponent(const std::weak_ptr<Texture2D>& texturePoints, int points, int animationStartRow, int animationStartCol)
	: m_pTexturePoints{texturePoints}
	, m_Points{points}
	, m_TimerBeforePickup{.5f}
	, m_TimeBeforeDelete{4.f}
	, m_Timer{0}
	, m_CanPickUp{false}
	, m_StartRow{animationStartRow}
	, m_StartCol{animationStartCol}
{}

void ItemComponent::Update()
{
	m_Timer += GameTime::GetInstance().DeltaTime();
	if (m_Timer >= m_TimerBeforePickup)
		m_CanPickUp = true;
	else if (m_Timer >= m_TimeBeforeDelete)
		GetGameObject().lock()->Delete();

}

void ItemComponent::OnCollide(std::shared_ptr<BaseCollider> pOther)
{
	auto pOtherGameObject{pOther->GetGameObject().lock()};
	if (pOtherGameObject->CompareTag("Player") && m_CanPickUp)
	{
		Prefabs::Points(GetTransform().GetPosition(), m_pTexturePoints, m_StartRow, m_StartCol);
		GetGameObject().lock()->Delete();
	}
}
