#include "TestScene.h"

#include <memory>

#include "SDL_pixels.h"
#include "SDL_rect.h"

#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "..\LevelBuilder.h"

using namespace OatmealEngine;

TestScene::TestScene()
	: BaseScene("TestScene")
{}

void TestScene::Initialize()
{
	LoadResources();
	auto& resourceManager{ResourceManager::GetInstance()};


#pragma region Test components
	
#pragma endregion

#pragma region Test game objects
	// Level
	LevelBuilder::Build(1, this, resourceManager.LoadTexture("Blocks").lock());

	// Player
	auto go = NewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Characters"), SDL_Point{16, 16}, 0, 0));
	go->AddComponent(std::make_shared<ControllerComponent>(350.f,0.f, 500.f));

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
			AnimationComponent::FrameDesc(0,0,.1f),
			AnimationComponent::FrameDesc(0,1,.1f),
			AnimationComponent::FrameDesc(0,2,.1f),
			AnimationComponent::FrameDesc(0,3,.1f),
			AnimationComponent::FrameDesc(0,4,.1f),
			AnimationComponent::FrameDesc(0,5,.1f),
			AnimationComponent::FrameDesc(0,6,.1f),
			AnimationComponent::FrameDesc(0,7,.1f),
		}
	);

	go->GetTransform().SetPosition(8*3*4, 500);
	go->GetTransform().SetScale(3,3);

	// FPS display
	go = NewGameObject();
	go->AddComponent(std::make_shared<FPSComponent>(resourceManager.LoadFont("Lingua24"), SDL_Color{245, 229, 220}));
	go->GetTransform().SetPosition(800, 0);

#pragma endregion
}

void TestScene::LoadResources() const
{
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("Blocks", "blocks.png");
	resourceManager.AddTexture("Characters", "characters.png");

	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
}
