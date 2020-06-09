#include "MiniginPCH.h"
#include "GameObject.h"

#include "Renderer.h"
#include "ResourceManager.h"

OatmealEngine::GameObject::~GameObject()
{
	OutputDebugString("Destructor: GameObject\n");
}

void OatmealEngine::GameObject::Awake()
{
	for (const auto& component : m_pComponents)
		component->Awake();
}

void OatmealEngine::GameObject::Start()
{
	for (const auto& component : m_pComponents)
		component->Start();
}

void OatmealEngine::GameObject::FixedUpdate()
{
	for (const auto& component : m_pComponents)
		component->FixedUpdate();
}

void OatmealEngine::GameObject::Update()
{
	for (const auto& component : m_pComponents)
		component->Update();
}

void OatmealEngine::GameObject::LateUpdate()
{
	for (const auto& component : m_pComponents)
		component->LateUpdate();
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
