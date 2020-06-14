#include "Minigin.h"

#if _DEBUG
#include <vld.h>
#endif

#include <memory>

#include "Scenes/MainScene.h"
#include "Scenes/MenuScene.h"
#include "SceneManager.h"
#include "GameSettings.h"

void InitScenes()
{
	OatmealEngine::SceneManager::GetInstance().AddScene(std::make_shared<MainScene>());
	OatmealEngine::SceneManager::GetInstance().AddScene(std::make_shared<MenuScene>());
	OatmealEngine::SceneManager::GetInstance().SetStartScene("MenuScene");
}

int main()
{
	// GameSettings
	OatmealEngine::GameSettings::WindowSettings.Width = 1200;
	OatmealEngine::GameSettings::WindowSettings.Height = 600;
	OatmealEngine::GameSettings::WindowSettings.VSync = false;
	OatmealEngine::GameSettings::WindowSettings.Name = "OatmealEngine";
	OatmealEngine::GameSettings::Gravity = {0,750.f};
	OatmealEngine::GameSettings::GlobalScale = 3;

	// Initialize all the scenes
	InitScenes();

	// Start the engine
	OatmealEngine::Minigin engine;
	engine.Run();

	return 0;
}