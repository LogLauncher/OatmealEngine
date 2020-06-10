#include "MiniginPCH.h"
#include "BaseComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"

std::weak_ptr<OatmealEngine::GameObject> OatmealEngine::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}

OatmealEngine::TransformComponent& OatmealEngine::BaseComponent::GetTransform() const
{
	return m_pGameObject.lock()->GetTransform();
}

void OatmealEngine::BaseComponent::SetGameObject(std::weak_ptr<GameObject> pGameObject)
{
	m_pGameObject = pGameObject;
}

