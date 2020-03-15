#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::m_IdCounter = 0;

dae::Scene::Scene(const std::string& name)
	: m_Name(name)
{}

void dae::Scene::Add(const std::shared_ptr<dae::GameObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void dae::Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

