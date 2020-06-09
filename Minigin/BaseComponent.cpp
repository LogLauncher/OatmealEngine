#include "MiniginPCH.h"
#include "BaseComponent.h"

#include "GameObject.h"

std::weak_ptr<OatmealEngine::GameObject> OatmealEngine::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}

void OatmealEngine::BaseComponent::SetGameObject(std::weak_ptr<GameObject> pGameObject)
{
	m_pGameObject = pGameObject;
}

