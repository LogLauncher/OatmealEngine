#include "MenuScene.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "..\Systems\GameManager.h"

using namespace OatmealEngine;

MenuScene::MenuScene()
	: BaseScene("MenuScene")
{}

void MenuScene::Initialize()
{
	InputManager::GetInstance().AddInputAction(InputAction("StartGame", InputTriggerState::Pressed, SDLK_RETURN));
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
