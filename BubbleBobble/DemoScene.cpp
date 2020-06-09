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
	auto go{GetNewGameObject()};
	go->AddComponent(std::make_shared<TextureComponent>("background.jpg"));

	go = GetNewGameObject();
	go->AddComponent(std::make_shared<TextureComponent>("logo.png"));
	go->GetTransform().SetPosition(216, 180);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = GetNewGameObject();
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	go->GetTransform().SetPosition(80, 20);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = GetNewGameObject();
	auto fpsComp{std::make_shared<FPSComponent>(font, SDL_Color{255,255,0})};
	go->AddComponent(fpsComp);
}
