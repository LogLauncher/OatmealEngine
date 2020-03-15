#include "MiniginPCH.h"

#include "BaseComponent.h"
#include "GameObject.h"

dae::BaseComponent::~BaseComponent()
{
	OutputDebugString("Destructor: BaseComponent\n");

}

std::weak_ptr<dae::GameObject> dae::BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}

void dae::BaseComponent::SetGameObject(std::weak_ptr<GameObject> pGameObject)
{
	m_pGameObject = pGameObject;
}

