#include "DemoScene.h"

#include <memory>

#include "GameObject.h"
#include "Components.h"
#include "ResourceManager.h"
#include "SDL_pixels.h"

using namespace OatmealEngine;

DemoScene::DemoScene()
	: BaseScene("DemoScene")
{}

void DemoScene::Initialize()
{
	LoadResources();
	auto& resourceManager{ResourceManager::GetInstance()};

	auto go{GetNewGameObject()};
	go->AddComponent(std::make_shared<TextureComponent>(resourceManager.LoadTexture("BaseBackground")));

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<TextureComponent>(resourceManager.LoadTexture("DAELogo")));
	go->AddComponent(std::make_shared<ControllerComponent>());
	go->GetTransform().SetPosition(216, 180);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", resourceManager.LoadFont("Lingua36")));
	go->GetTransform().SetPosition(80, 20);

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<FPSComponent>(resourceManager.LoadFont("Lingua24"), SDL_Color{255,255,0}));

}

void DemoScene::LoadResources() const
{
	auto& resourceManager{ResourceManager::GetInstance()};
	resourceManager.AddTexture("BaseBackground", "background.jpg");
	resourceManager.AddTexture("DAELogo", "logo.png");
	resourceManager.AddFont("Lingua36", "Lingua.otf", 36);
	resourceManager.AddFont("Lingua24", "Lingua.otf", 24);
}
