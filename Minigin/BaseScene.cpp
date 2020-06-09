#include "MiniginPCH.h"
#include "BaseScene.h"

#include "GameObject.h"

OatmealEngine::BaseScene::BaseScene(const std::string& name)
	: m_Name(name)
	, m_IsInitialized{false}
{}

std::shared_ptr<OatmealEngine::GameObject> OatmealEngine::BaseScene::GetNewGameObject()
{
	auto gameObject{std::make_shared<GameObject>()};
	m_Objects.push_back(gameObject);
	return gameObject;
}

bool OatmealEngine::BaseScene::Remove(const std::shared_ptr<GameObject>& object)
{
	auto it = find(m_Objects.begin(), m_Objects.end(), object);
	if (it == m_Objects.end())
		return false;

	m_Objects.erase(it);
	return true;
}

void OatmealEngine::BaseScene::RootAwake()
{
	for (auto& object : m_Objects)
		object->RootAwake();
}

void OatmealEngine::BaseScene::RootStart()
{
	for (auto& object : m_Objects)
		object->RootStart();
}

void OatmealEngine::BaseScene::RootFixedUpdate()
{
	for (auto& object : m_Objects)
		object->RootFixedUpdate();
}

void OatmealEngine::BaseScene::RootUpdate()
{
	for(auto& object : m_Objects)
		object->RootUpdate();
}

void OatmealEngine::BaseScene::RootLateUpdate()
{
	for (auto& object : m_Objects)
		object->RootLateUpdate();
}

void OatmealEngine::BaseScene::RootRender() const
{
	for (const auto& object : m_Objects)
		object->RootRender();
}
