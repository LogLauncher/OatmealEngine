#include "MiniginPCH.h"
#include "SceneManager.h"

#include "Scene.h"

std::shared_ptr<OatmealEngine::Scene> OatmealEngine::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::make_shared<Scene>(name);
	m_Scenes.push_back(scene);
	return scene;
}

void OatmealEngine::SceneManager::Awake()
{
	for (const auto& scene : m_Scenes)
		scene->Awake();
}

void OatmealEngine::SceneManager::Start()
{
	for (const auto& scene : m_Scenes)
		scene->Start();
}

void OatmealEngine::SceneManager::FixedUpdate()
{
	for(auto& scene : m_Scenes)
		scene->FixedUpdate();
}

void OatmealEngine::SceneManager::Update()
{
	for (const auto& scene : m_Scenes)
		scene->Update();
}

void OatmealEngine::SceneManager::LateUpdate()
{
	for (const auto& scene : m_Scenes)
		scene->LateUpdate();
}

void OatmealEngine::SceneManager::Render() const
{
	for (const auto& scene : m_Scenes)
		scene->Render();
}
