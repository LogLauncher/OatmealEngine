#include "MainScene.h"

#include <memory>

#include "SDL_pixels.h"
#include "SDL_rect.h"

#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "..\LevelBuilder.h"
#include "..\Components\PlayerComponent.h"

using namespace OatmealEngine;

MainScene::MainScene()
	: BaseScene("MainScene")
{}

void MainScene::Initialize()
{
	LoadResources();
	auto& resourceManager{ResourceManager::GetInstance()};

	// Level
	LevelBuilder::Build(1, this, resourceManager.LoadTexture("Blocks").lock());

#pragma region Player 1
	// Player 1
	{
		const int spriteRow{0};
		auto go = NewGameObject();
		go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Characters"), SDL_Point{16, 16}, spriteRow, 0));
		go->AddComponent(std::make_shared<PlayerComponent>(PlayerIndex::PlayerOne));

		auto collider = go->AddComponent(std::make_shared<ColliderComponent>(14, 16));
		go->AddComponent(std::make_shared<RigidbodyComponent>(collider));

		auto animation = go->AddComponent(std::make_shared<AnimationComponent>());
		animation->AddAnimation("Idle",
			{
				AnimationComponent::FrameDesc(spriteRow,0,-1),
			}
		);
		animation->AddAnimation("Move",
			{
				AnimationComponent::FrameDesc(spriteRow,0,.05f),
				AnimationComponent::FrameDesc(spriteRow,1,.05f),
				AnimationComponent::FrameDesc(spriteRow,2,.05f),
				AnimationComponent::FrameDesc(spriteRow,3,.05f),
				AnimationComponent::FrameDesc(spriteRow,4,.05f),
				AnimationComponent::FrameDesc(spriteRow,5,.05f),
				AnimationComponent::FrameDesc(spriteRow,6,.05f),
				AnimationComponent::FrameDesc(spriteRow,7,.05f),
			}
		);

		go->GetTransform().SetPosition(8 * 3 * 4, 500);
		go->GetTransform().SetScale(3, 3);
	}
#pragma endregion

#pragma region Player 2
// 	// Player 2
// 	{
// 		const int spriteRow{3};
// 		auto go = NewGameObject();
// 		go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Characters"), SDL_Point{16, 16}, spriteRow, 0));
// 		go->AddComponent(std::make_shared<PlayerComponent>(PlayerIndex::PlayerTwo));
// 
// 		auto collider = go->AddComponent(std::make_shared<ColliderComponent>(14, 16));
// 		go->AddComponent(std::make_shared<RigidbodyComponent>(collider));
// 
// 		auto animation = go->AddComponent(std::make_shared<AnimationComponent>());
// 		animation->AddAnimation("Idle",
// 			{
// 				AnimationComponent::FrameDesc(spriteRow,0,-1),
// 			}
// 		);
// 		animation->AddAnimation("Move",
// 			{
// 				AnimationComponent::FrameDesc(spriteRow,0,.05f),
// 				AnimationComponent::FrameDesc(spriteRow,1,.05f),
// 				AnimationComponent::FrameDesc(spriteRow,2,.05f),
// 				AnimationComponent::FrameDesc(spriteRow,3,.05f),
// 				AnimationComponent::FrameDesc(spriteRow,4,.05f),
// 				AnimationComponent::FrameDesc(spriteRow,5,.05f),
// 				AnimationComponent::FrameDesc(spriteRow,6,.05f),
// 				AnimationComponent::FrameDesc(spriteRow,7,.05f),
// 			}
// 		);
// 
// 		go->GetTransform().SetPosition(8 * 3 * 15, 500);
// 		go->GetTransform().SetScale(3, 3);
// 	}
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

	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
}