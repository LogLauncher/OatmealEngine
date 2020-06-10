#include "MiniginPCH.h"
#include "BaseScene.h"

#include "GameObject.h"
#include "RenderComponent.h"

OatmealEngine::BaseScene::BaseScene(const std::string& name)
	: m_Name(name)
	, m_IsInitialized{false}
{}

void OatmealEngine::BaseScene::AddRenderComponent(const std::shared_ptr<RenderComponent>& pRenderComponent)
{
	m_pRenderComponents.push_back(pRenderComponent);
}

std::shared_ptr<OatmealEngine::GameObject> OatmealEngine::BaseScene::GetNewGameObject()
{
	auto gameObject{std::make_shared<GameObject>()};
	gameObject->SetScene(shared_from_this());
	m_pObjects.push_back(gameObject);
	return gameObject;
}

bool OatmealEngine::BaseScene::Remove(const std::shared_ptr<GameObject>& object)
{
	auto it = find(m_pObjects.begin(), m_pObjects.end(), object);
	if (it == m_pObjects.end())
		return false;

	m_pObjects.erase(it);
	return true;
}

void OatmealEngine::BaseScene::RootStart()
{
	for (auto& object : m_pObjects)
		object->RootStart();
}

void OatmealEngine::BaseScene::RootFixedUpdate()
{
	for (auto& object : m_pObjects)
		object->RootFixedUpdate();
}

void OatmealEngine::BaseScene::RootUpdate()
{
	for(auto& object : m_pObjects)
		object->RootUpdate();
}

void OatmealEngine::BaseScene::RootLateUpdate()
{
	for (auto& object : m_pObjects)
		object->RootLateUpdate();
}

void OatmealEngine::BaseScene::RootRender() const
{
	for (const auto& component : m_pRenderComponents)
		component->Render();
}
