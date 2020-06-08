#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void OatmealEngine::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void OatmealEngine::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

std::shared_ptr<OatmealEngine::Scene> OatmealEngine::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::make_shared<Scene>(name);
	m_Scenes.push_back(scene);
	return scene;
}
