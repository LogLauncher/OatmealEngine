#include "MainScene.h"

#include <memory>

#include "SDL_pixels.h"
#include "SDL_rect.h"

#include "GameObject.h"
#include "Components.h"
#include "../Systems/GameManager.h"
#include "ResourceManager.h"
#include "../Systems/LevelBuilder.h"
#include "../Components/PlayerComponent.h"
#include "../Systems/Prefabs.h"

using namespace OatmealEngine;

MainScene::MainScene()
	: BaseScene("MainScene")
{}

void MainScene::Initialize()
{
	LoadResources();
	auto& resourceManager{ResourceManager::GetInstance()};

	// GameManager
	GameManager::GetInstance().Initialize();


	// FPS display
	{
		auto go = NewGameObject();
		go->AddComponent(std::make_shared<FPSComponent>(resourceManager.LoadFont("Lingua24"), SDL_Color{245, 229, 220}));
		go->GetTransform().SetPosition(800, 0);
	}

}

void MainScene::LoadResources() const
{
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("Blocks", "blocks.png");
	resourceManager.AddTexture("Characters", "characters.png");
	resourceManager.AddTexture("Misc", "misc.png");

	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
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
