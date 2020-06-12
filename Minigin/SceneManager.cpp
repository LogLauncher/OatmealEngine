#include "MiniginPCH.h"
#include "SceneManager.h"

#include "BaseScene.h"

void OatmealEngine::SceneManager::Initialize()
{
	for (auto& scene : m_pScenes)
		scene.second->Initialize();

	auto pActiveScene{m_pActiveScene.lock()};
	if (!pActiveScene->m_IsInitialized)
	{
		pActiveScene->RootStart();
		pActiveScene->OnSceneLoad();
		pActiveScene->m_IsInitialized = true;
	}
}

void OatmealEngine::SceneManager::AddScene(const std::shared_ptr<BaseScene>& scene)
{
	m_pScenes.insert(std::make_pair(scene->GetName(), scene));
}
bool OatmealEngine::SceneManager::SetStartScene(const std::string& name)
{
	// Check if exists
	auto it = m_pScenes.find(name);
	if (it == m_pScenes.end())
		return false;

	auto sceneToLoad{(*it).second};
	m_pActiveScene = sceneToLoad;

	return true;
}
bool OatmealEngine::SceneManager::LoadScene(const std::string& name)
{
	auto it = m_pScenes.find(name);
	if (it == m_pScenes.end())
		return false;

	auto sceneToLoad{(*it).second};
	if (!sceneToLoad->m_IsInitialized)
	{
		sceneToLoad->RootStart();
		sceneToLoad->m_IsInitialized = true;
	}

	m_pActiveScene.lock()->OnSceneUnload();
	m_pActiveScene = sceneToLoad;
	m_pActiveScene.lock()->OnSceneLoad();

	return true;
}

void OatmealEngine::SceneManager::RootFixedUpdate() const
{
	m_pActiveScene.lock()->RootFixedUpdate();
}
void OatmealEngine::SceneManager::RootUpdate() const
{
	m_pActiveScene.lock()->RootUpdate();
}
void OatmealEngine::SceneManager::RootLateUpdate() const
{
	m_pActiveScene.lock()->RootLateUpdate();
}
void OatmealEngine::SceneManager::RootRender() const
{
	m_pActiveScene.lock()->RootRender();
}

void OatmealEngine::SceneManager::RootUpdateCollision() const
{
	m_pActiveScene.lock()->UpdateCollision();
}


#ifdef _DEBUG
void OatmealEngine::SceneManager::RootDebugRender() const
{
	m_pActiveScene.lock()->RootDebugRender();
}
#endif
