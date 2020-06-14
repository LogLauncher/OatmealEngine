#include "MenuScene.h"

#include "GameObject.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "..\Systems\GameManager.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"

using namespace OatmealEngine;

MenuScene::MenuScene()
	: BaseScene("MenuScene")
{}

void MenuScene::Initialize()
{
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("Menu", "menu_background.png");

	InputManager::GetInstance().AddInputAction(InputAction("StartGame", InputTriggerState::Pressed, SDLK_RETURN));

	auto go{NewGameObject()};
	go->AddComponent(std::make_shared<SpriteComponent>(ResourceManager::GetInstance().LoadTexture("Menu")));
	go->GetTransform().SetScale({1.f / GameSettings::GlobalScale, 1.f / GameSettings::GlobalScale});
}

void MenuScene::Update()
{
	GameManager::GetInstance().Update();

	if (InputManager::GetInstance().IsActionTriggered("StartGame", PlayerIndex::PlayerOne))
	{
		SceneManager::GetInstance().LoadScene("MainScene");
		GameManager::GetInstance().SetState(GameManager::State::GAME);
	}
}
