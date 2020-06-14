#include "MainScene.h"

#include <memory>

#include "SDL_pixels.h"
#include "SDL_rect.h"

#include "GameObject.h"
#include "Components.h"
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

	// Level
	LevelBuilder::Build(1, this, resourceManager.LoadTexture("Blocks").lock());

#pragma region Player 1
	// Player 1
	{
		auto go = NewGameObject();
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

#pragma region Player 2
	// Player 2
	{
		auto go = NewGameObject();
		go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Characters"), SDL_Point{16, 16}, 3, 0));
		go->AddComponent(std::make_shared<PlayerComponent>(PlayerIndex::PlayerTwo));

		auto collider = go->AddComponent(std::make_shared<ColliderComponent>(16, 16));
		go->AddComponent(std::make_shared<RigidbodyComponent>(collider));

		auto animation = go->AddComponent(std::make_shared<AnimationComponent>());
		animation->AddAnimation("Idle",
			{
				AnimationComponent::FrameDesc(3,0,-1),
			}
		);
		animation->AddAnimation("Move",
			{
				AnimationComponent::FrameDesc(3,0,.05f),
				AnimationComponent::FrameDesc(3,1,.05f),
				AnimationComponent::FrameDesc(3,2,.05f),
				AnimationComponent::FrameDesc(3,3,.05f),
				AnimationComponent::FrameDesc(3,4,.05f),
				AnimationComponent::FrameDesc(3,5,.05f),
				AnimationComponent::FrameDesc(3,6,.05f),
				AnimationComponent::FrameDesc(3,7,.05f),
			}
		);
		animation->AddAnimation("Shoot",
			{
				AnimationComponent::FrameDesc(4, 0, .1f),
				AnimationComponent::FrameDesc(4, 4, .1f),
				AnimationComponent::FrameDesc(4, 0, .1f),
			}
		);
		animation->AddAnimation("Hit",
			{
				AnimationComponent::FrameDesc(5,0,.075f),
				AnimationComponent::FrameDesc(5,1,.075f),
				AnimationComponent::FrameDesc(5,2,.075f),
				AnimationComponent::FrameDesc(5,3,.075f),
			}
		);
		go->GetTransform().SetPosition(8 * GameSettings::GlobalScale * 26, 500);
		go->GetTransform().SetScale(-1, 1);
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
