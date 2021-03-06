#include "MainScene.h"

#include <memory>

#include "SDL_pixels.h"
#include "SDL_rect.h"

#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "../Systems/Prefabs.h"
#include "../Systems/GameManager.h"
#include "../Systems/LevelBuilder.h"
#include "../Components/PlayerComponent.h"

using namespace OatmealEngine;

MainScene::MainScene()
	: BaseScene("MainScene")
{}

void MainScene::Initialize()
{
	// Resources
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("Blocks", "blocks.png");
	resourceManager.AddTexture("Characters", "characters.png");
	resourceManager.AddTexture("Misc", "misc.png");

	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
	
	// GameManager
	GameManager::GetInstance().Initialize();

}

void MainScene::Update()
{
	GameManager::GetInstance().Update();
}

void MainScene::OnSceneLoad()
{
	GameManager::GetInstance().LoadLevel();

	Prefabs::Player({8 * GameSettings::GlobalScale * 4, 8 * GameSettings::GlobalScale * 20, 0}, PlayerIndex::PlayerOne, 0);
}
