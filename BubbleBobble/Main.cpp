#include "Minigin.h"

#if _DEBUG
#include <vld.h>
#endif

#include <memory>

#include "Scenes/TestScene.h"
#include "SceneManager.h"
#include "GameSettings.h"

void InitScenes()
{
	OatmealEngine::SceneManager::GetInstance().AddScene(std::make_shared<TestScene>());
	OatmealEngine::SceneManager::GetInstance().SetStartScene("TestScene");
}

int main()
{
	// GameSettings
	OatmealEngine::GameSettings::WindowSettings.Width = 1920;
	OatmealEngine::GameSettings::WindowSettings.Height = 1080;
	OatmealEngine::GameSettings::WindowSettings.VSync = false;

	// Initialize all the scenes
	InitScenes();

	// Start the engine
	OatmealEngine::Minigin engine;
	engine.Run();

	return 0;
}