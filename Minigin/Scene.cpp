#include "MiniginPCH.h"
#include "Scene.h"

#include "GameObject.h"

OatmealEngine::Scene::Scene(const std::string& name)
	: m_Name(name)
{}

void OatmealEngine::Scene::Add(const std::shared_ptr<OatmealEngine::GameObject>& object)
{
	m_Objects.push_back(object);
}

bool OatmealEngine::Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	auto it = find(m_Objects.begin(), m_Objects.end(), object);
	if (it == m_Objects.end())
		return false;

	m_Objects.erase(it);
	return true;
}

void OatmealEngine::Scene::RootFixedUpdate()
{
	for (auto& object : m_Objects)
		object->RootFixedUpdate();
}

void OatmealEngine::Scene::RootUpdate()
{
	for(auto& object : m_Objects)
		object->RootUpdate();
}

void OatmealEngine::Scene::RootLateUpdate()
{
	for (auto& object : m_Objects)
		object->RootLateUpdate();
}

void OatmealEngine::Scene::RootRender() const
{
	for (const auto& object : m_Objects)
		object->RootRender();
}
