#include "DemoScene.h"

#include <memory>

#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"

using namespace OatmealEngine;

DemoScene::DemoScene()
	: BaseScene("DemoScene")
{}

void DemoScene::Initialize()
{
	LoadResources();
	auto& resourceManager{ResourceManager::GetInstance()};

	auto go{GetNewGameObject()};
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("Blocks"), SDL_Point{8, 8}, 0, 9));
	go->GetTransform().SetPosition(500, 500);
	go->GetTransform().SetScale(5,5);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("BaseBackground")));

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<SpriteComponent>(resourceManager.LoadTexture("DAELogo")));
	go->AddComponent(std::make_shared<ControllerComponent>());
	go->GetTransform().SetPosition(216, 180);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", resourceManager.LoadFont("Lingua36")));
	go->GetTransform().SetPosition(80, 20);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<FPSComponent>(resourceManager.LoadFont("Lingua36"), SDL_Color{200,200,200}));

}

void DemoScene::LoadResources() const
{
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("Blocks", "blocks.png");
	resourceManager.AddTexture("BaseBackground", "background.jpg");
	resourceManager.AddTexture("DAELogo", "logo.png");
	resourceManager.AddFont("Lingua36", "Lingua.otf", 36);
	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
}
