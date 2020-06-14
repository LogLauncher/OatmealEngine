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

#pragma region Player 1
	// Player 1
	{
		auto go = NewGameObject();
		go->SetTag("Player");
		go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Characters"), SDL_Point{16, 16}, 0, 0));
		go->AddComponent(std::make_shared<PlayerComponent>(PlayerIndex::PlayerOne));

		auto collider = go->AddComponent(std::make_shared<ColliderComponent>(16, 16));
		go->AddComponent(std::make_shared<RigidbodyComponent>(collider));

		auto animation = go->AddComponent(std::make_shared<AnimationComponent>());
		animation->AddAnimation("Idle",
			{
				AnimationComponent::FrameDesc(0,0,-1),
			}
		);
		animation->AddAnimation("Move",
			{
				AnimationComponent::FrameDesc(0,0,.05f),
				AnimationComponent::FrameDesc(0,1,.05f),
				AnimationComponent::FrameDesc(0,2,.05f),
				AnimationComponent::FrameDesc(0,3,.05f),
				AnimationComponent::FrameDesc(0,4,.05f),
				AnimationComponent::FrameDesc(0,5,.05f),
				AnimationComponent::FrameDesc(0,6,.05f),
				AnimationComponent::FrameDesc(0,7,.05f),
			}
		);
		animation->AddAnimation("Shoot",
			{
				AnimationComponent::FrameDesc(1,0,.1f),
				AnimationComponent::FrameDesc(1,4,.1f),
				AnimationComponent::FrameDesc(1,0,.1f),
			}
		);
		animation->AddAnimation("Hit",
			{
				AnimationComponent::FrameDesc(2,0,.075f),
				AnimationComponent::FrameDesc(2,1,.075f),
				AnimationComponent::FrameDesc(2,2,.075f),
				AnimationComponent::FrameDesc(2,3,.075f),
			}
		);

		go->GetTransform().SetPosition(8 * GameSettings::GlobalScale * 4, 500);
	}
#pragma endregion

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
}
