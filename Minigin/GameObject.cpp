#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseScene.h"
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "RigidbodyComponent.h"

OatmealEngine::GameObject::GameObject()
	: m_Tag{""}
{}

void OatmealEngine::GameObject::RootAwake()
{
	for (const auto& component : m_pComponents)
		component->Awake();
}

void OatmealEngine::GameObject::RootStart()
{
	for (const auto& component : m_pComponents)
		component->Start();
}

void OatmealEngine::GameObject::RootFixedUpdate()
{
	for (const auto& component : m_pComponents)
		component->FixedUpdate();
}

void OatmealEngine::GameObject::RootUpdate()
{
	for (const auto& component : m_pComponents)
		component->Update();
}

void OatmealEngine::GameObject::RootLateUpdate()
{
	for (const auto& component : m_pComponents)
		component->LateUpdate();
}

OatmealEngine::TransformComponent& OatmealEngine::GameObject::GetTransform()
{
	return m_Transform;
}

std::shared_ptr<OatmealEngine::RenderComponent> OatmealEngine::GameObject::AddComponent(const std::shared_ptr<RenderComponent>& pComponent)
{
	m_pComponents.push_back(pComponent);
	m_pBaseScene.lock()->AddRenderComponent(pComponent);
	pComponent->SetGameObject(shared_from_this());
	return pComponent;
}

std::shared_ptr<OatmealEngine::RigidbodyComponent> OatmealEngine::GameObject::AddComponent(const std::shared_ptr<RigidbodyComponent>& pComponent)
{
	m_pComponents.push_back(pComponent);
	m_pBaseScene.lock()->AddRigidbodyComponent(pComponent);
	pComponent->SetGameObject(shared_from_this());
	pComponent->Awake();
	return pComponent;
}

std::weak_ptr<OatmealEngine::BaseScene> OatmealEngine::GameObject::GetScene() const
{
	return m_pBaseScene;
}

void OatmealEngine::GameObject::SetScene(const std::weak_ptr<BaseScene>& pBaseScene)
{
	m_pBaseScene = pBaseScene;
}

#ifdef _DEBUG
void OatmealEngine::GameObject::RootDebugRender() const
{
	for (const auto& component : m_pComponents)
		component->DebugRender();
}
#endif // _DEBUG

void OatmealEngine::GameObject::Delete()
{
	m_pBaseScene.lock()->Remove(shared_from_this());
}
