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
	auto go = GetNewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("BaseBackground")));

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("DAELogo")));
	go->AddComponent(std::make_shared<ControllerComponent>());
	go->GetTransform().SetPosition(216, 180);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", resourceManager.LoadFont("Lingua36")));
	go->GetTransform().SetPosition(80, 30);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<FPSComponent>(resourceManager.LoadFont("Lingua24"), SDL_Color{245, 229, 27}));
#pragma endregion

#pragma region Test game objects
	go = GetNewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Blocks"), SDL_Point{8, 8}, 0, 0));
	go->GetTransform().SetPosition(720, 0);
	go->GetTransform().SetScale(5,5);

	CreateBlock(17, 11, 0, 0);
	CreateBlock(17, 12, 0, 0);
	CreateBlock(17, 13, 0, 0);
	CreateBlock(17, 14, 0, 0);
	CreateBlock(17, 15, 0, 0);
	CreateBlock(18, 15, 0, 0);
	CreateBlock(19, 15, 0, 0);
	CreateBlock(20, 15, 0, 0);
	CreateBlock(21, 15, 0, 0);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Characters"), SDL_Point{16, 16}, 0, 0));
	go->AddComponent(std::make_shared<ControllerComponent>());
	auto collider = std::make_shared<ColliderComponent>(16,16);
	go->AddComponent(collider);
	go->AddComponent(std::make_shared<RigidbodyComponent>(collider));
	go->GetTransform().SetPosition(720, 0);
	go->GetTransform().SetScale(5,5);
#pragma endregion
}

void TestScene::LoadResources() const
{
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("Blocks", "blocks.png");
	resourceManager.AddTexture("Characters", "characters.png");

	resourceManager.AddTexture("BaseBackground", "background.jpg");
	resourceManager.AddTexture("DAELogo", "logo.png");
	resourceManager.AddFont("Lingua36", "Lingua.otf", 36);
	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
}

void TestScene::CreateBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet)
{
	const SDL_Point blockSize{8, 8};
	const float scale{5};

	auto go = GetNewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(ResourceManager::GetInstance().LoadTexture("Blocks"), blockSize, rowSpriteSheet, colSpriteSheet));
	auto collider{std::make_shared<ColliderComponent>(blockSize)};
	go->AddComponent(collider);
	go->AddComponent(std::make_shared<RigidbodyComponent>(collider, true));
	go->GetTransform().SetPosition(rowWorld * blockSize.x * scale, colWorld * blockSize.y * scale);
	go->GetTransform().SetScale(scale, scale);
}
