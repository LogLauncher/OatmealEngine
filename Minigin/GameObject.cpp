#include "MiniginPCH.h"
#include "GameObject.h"

#include "Renderer.h"
#include "ResourceManager.h"

OatmealEngine::GameObject::~GameObject()
{
	OutputDebugString("Destructor: GameObject\n");
}

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

void OatmealEngine::GameObject::RootRender() const
{
	for (const auto& component : m_pComponents)
		component->Render();
}

OatmealEngine::TransformComponent& OatmealEngine::GameObject::GetTransform()
{
	return m_Transform;
}

void OatmealEngine::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
	component->SetGameObject(shared_from_this());
}
