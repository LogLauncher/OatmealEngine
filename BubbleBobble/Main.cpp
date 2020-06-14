#include "Minigin.h"

#if _DEBUG
#include <vld.h>
#endif

#include <memory>

#include "Scenes/MainScene.h"
#include "Scenes/MenuScene.h"
#include "SceneManager.h"
#include "GameSettings.h"

using namespace OatmealEngine;

void InitScenes()
{
	SceneManager::GetInstance().AddScene(std::make_shared<MainScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<MenuScene>());
	SceneManager::GetInstance().SetStartScene("MenuScene");
}

int main()
{
	// GameSettings
	GameSettings::WindowSettings.Width = 1200;
	GameSettings::WindowSettings.Height = 600;
	GameSettings::WindowSettings.VSync = false;
	GameSettings::WindowSettings.Name = "OatmealEngine";
	GameSettings::Gravity = {0,750.f};
	GameSettings::GlobalScale = 3;

	// Initialize all the scenes
	InitScenes();

	// Start the engine
	OatmealEngine::Minigin engine;
	engine.Run();

	return 0;
}