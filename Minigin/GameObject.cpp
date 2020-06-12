#include "MiniginPCH.h"
#include "GameObject.h"

#include "BaseScene.h"
#include "BaseComponent.h"
#include "RenderComponent.h"

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

void OatmealEngine::GameObject::AddComponent(const std::shared_ptr<BaseComponent>& pComponent)
{
	m_pComponents.push_back(pComponent);
	pComponent->SetGameObject(shared_from_this());
	pComponent->Awake();
}

void OatmealEngine::GameObject::AddComponent(const std::shared_ptr<RenderComponent>& pComponent)
{
	m_pBaseScene.lock()->AddRenderComponent(pComponent);
	pComponent->SetGameObject(shared_from_this());
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
