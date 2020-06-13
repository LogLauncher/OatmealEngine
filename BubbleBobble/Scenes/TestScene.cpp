#include "TestScene.h"

#include <memory>

#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"

using namespace OatmealEngine;

TestScene::TestScene()
	: BaseScene("TestScene")
{}

void TestScene::Initialize()
{
	LoadResources();
	auto& resourceManager{ResourceManager::GetInstance()};

#pragma region Test components
	auto go = NewGameObject();
	go->AddComponent(std::make_shared<FPSComponent>(resourceManager.LoadFont("Lingua24"), SDL_Color{245, 229, 27}));
#pragma endregion

#pragma region Test game objects

	// Level
	CreateBlock(0, 3, 0, 0);
	CreateBlock(0, 4, 0, 0);
	CreateBlock(0, 5, 0, 0);
	CreateBlock(0, 6, 0, 0);
	CreateBlock(0, 7, 0, 0);
	CreateBlock(0, 8, 0, 0);
	CreateBlock(0, 9, 0, 0);
	CreateBlock(0, 10, 0, 0);
	CreateBlock(0, 11, 0, 0);
	CreateBlock(0, 12, 0, 0);
	CreateBlock(0, 13, 0, 0);
	CreateBlock(0, 14, 0, 0);
	CreateBlock(0, 15, 0, 0);
	CreateBlock(1, 15, 0, 0);
	CreateBlock(2, 15, 0, 0);
	CreateBlock(3, 15, 0, 0);
	CreateBlock(4, 15, 0, 0);
	CreateBlock(5, 15, 0, 0);
	CreateBlock(6, 15, 0, 0);
	CreateBlock(7, 15, 0, 0);
	CreateBlock(8, 15, 0, 0);
	CreateBlock(9, 15, 0, 0);
	CreateBlock(10, 15, 0, 0);
	CreateBlock(11, 15, 0, 0);
	CreateBlock(12, 15, 0, 0);
	CreateBlock(13, 15, 0, 0);
	CreateBlock(14, 15, 0, 0);
	CreateBlock(15, 15, 0, 0);
	CreateBlock(16, 15, 0, 0);
	CreateBlock(17, 15, 0, 0);
	CreateBlock(18, 15, 0, 0);
	CreateBlock(19, 15, 0, 0);
	CreateBlock(20, 15, 0, 0);
	CreateBlock(21, 15, 0, 0);
	CreateBlock(22, 15, 0, 0);

	// Player
	go = NewGameObject();
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

	go->GetTransform().SetPosition(720, 0);
	go->GetTransform().SetScale(3,3);
#pragma endregion
}

void TestScene::LoadResources() const
{
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("Blocks", "blocks.png");
	resourceManager.AddTexture("Characters", "characters.png");

	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
}

void TestScene::CreateBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet)
{
	const SDL_Point blockSize{8, 8};
	const float scale{3};

	auto go = NewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(ResourceManager::GetInstance().LoadTexture("Blocks"), blockSize, rowSpriteSheet, colSpriteSheet));
	auto collider{std::make_shared<ColliderComponent>(blockSize)};
	go->AddComponent(collider);
	go->AddComponent(std::make_shared<RigidbodyComponent>(collider, true));
	go->GetTransform().SetPosition(rowWorld * blockSize.x * scale, colWorld * blockSize.y * scale);
	go->GetTransform().SetScale(scale, scale);
}
