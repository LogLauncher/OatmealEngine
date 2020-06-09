#include "MiniginPCH.h"
#include "SceneManager.h"

#include "BaseScene.h"

void OatmealEngine::SceneManager::Initialize()
{
	for (auto& scene : m_Scenes)
		scene.second->Initialize();

	if (!m_ActiveScene->m_IsInitialized)
	{
		m_ActiveScene->RootAwake();
		m_ActiveScene->RootStart();
		m_ActiveScene->OnSceneLoad();
		m_ActiveScene->m_IsInitialized = true;
	}
}

void OatmealEngine::SceneManager::AddScene(std::shared_ptr<BaseScene> scene)
{
	m_Scenes.insert(std::make_pair(scene->GetName(), scene));
}
bool OatmealEngine::SceneManager::SetStartScene(const std::string& name)
{
	auto it = m_Scenes.find(name);
	if (it == m_Scenes.end())
		return false;

	auto sceneToLoad{(*it).second};
	m_ActiveScene = sceneToLoad;

	return true;
}
bool OatmealEngine::SceneManager::LoadScene(const std::string& name)
{
	auto it = m_Scenes.find(name);
	if (it == m_Scenes.end())
		return false;

	auto sceneToLoad{(*it).second};
	if (!sceneToLoad->m_IsInitialized)
	{
		sceneToLoad->RootAwake();
		sceneToLoad->RootStart();
		sceneToLoad->m_IsInitialized = true;
	}

	m_ActiveScene->OnSceneUnload();
	m_ActiveScene = sceneToLoad;
	m_ActiveScene->OnSceneLoad();

	return true;
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
