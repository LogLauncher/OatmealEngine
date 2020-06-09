#include "MiniginPCH.h"
#include "SceneManager.h"

#include "Scene.h"

void OatmealEngine::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_Scenes.insert(std::make_pair(scene->GetName(), scene));
}

void OatmealEngine::SceneManager::RootFixedUpdate()
{
	m_ActiveScene->RootFixedUpdate();
}

void OatmealEngine::SceneManager::RootUpdate()
{
	m_ActiveScene->RootUpdate();
}

void OatmealEngine::SceneManager::RootLateUpdate()
{
	m_ActiveScene->RootLateUpdate();
}

void OatmealEngine::SceneManager::RootRender() const
{
	m_ActiveScene->RootRender();
}

bool OatmealEngine::SceneManager::LoadScene(const std::string& name)
{
	auto it = m_Scenes.find(name);
	if (it == m_Scenes.end())
		return false;

	auto oldScene{(*it).second};
	oldScene->OnSceneUnload();
	m_ActiveScene = oldScene;
	m_ActiveScene->OnSceneLoad();

	return true;
}

void OatmealEngine::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
		scene.second->Initialize();
}
