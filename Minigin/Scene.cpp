#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int OatmealEngine::Scene::m_IdCounter = 0;

OatmealEngine::Scene::Scene(const std::string& name)
	: m_Name(name)
{}

void OatmealEngine::Scene::Add(const std::shared_ptr<OatmealEngine::GameObject>& object)
{
	m_Objects.push_back(object);
}

void OatmealEngine::Scene::Awake()
{
	for (auto& object : m_Objects)
		object->Awake();
}

void OatmealEngine::Scene::Start()
{
	for (auto& object : m_Objects)
		object->Start();
}

void OatmealEngine::Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
		object->FixedUpdate();
}

void OatmealEngine::Scene::Update()
{
	for(auto& object : m_Objects)
		object->Update();
}

void OatmealEngine::Scene::LateUpdate()
{
	for (auto& object : m_Objects)
		object->LateUpdate();
}

void OatmealEngine::Scene::Render() const
{
	for (const auto& object : m_Objects)
		object->Render();
}
