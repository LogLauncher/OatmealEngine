#include "MiniginPCH.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

void dae::GameObject::Update(float deltaTime)
{
	for (const auto& component : m_pComponents)
		component->Update(deltaTime);
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
		component->Render();
}

dae::TransformComponent& dae::GameObject::GetTransform()
{
	return m_Transform;
}

void dae::GameObject::AddComponenet(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
	component->SetGameObject(shared_from_this());
}

dae::GameObject::~GameObject()
{
	OutputDebugString("Destructor: GameObject\n");
}
