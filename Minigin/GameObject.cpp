#include "MiniginPCH.h"
#include "GameObject.h"

#include "Renderer.h"
#include "ResourceManager.h"

void OatmealEngine::GameObject::Update(float deltaTime)
{
	for (const auto& component : m_pComponents)
		component->Update(deltaTime);
}

void OatmealEngine::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
		component->Render();
}

OatmealEngine::TransformComponent& OatmealEngine::GameObject::GetTransform()
{
	return m_Transform;
}

void OatmealEngine::GameObject::AddComponenet(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
	component->SetGameObject(shared_from_this());
}

OatmealEngine::GameObject::~GameObject()
{
	OutputDebugString("Destructor: GameObject\n");
}
