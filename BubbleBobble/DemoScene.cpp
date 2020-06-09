#include "DemoScene.h"

#include <memory>

#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "SDL_pixels.h"

DemoScene::DemoScene()
	: Scene("DemoScene")
{}

void DemoScene::Initialize()
{
	auto go{std::make_shared<OatmealEngine::GameObject>()};
	go->AddComponenet(std::make_shared<OatmealEngine::TextureComponent>("background.jpg"));
	Add(go);

	go = std::make_shared<OatmealEngine::GameObject>();
	go->AddComponenet(std::make_shared<OatmealEngine::TextureComponent>("logo.png"));
	go->GetTransform().SetPosition(216, 180);
	Add(go);

	auto font = OatmealEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<OatmealEngine::GameObject>();
	go->AddComponenet(std::make_shared<OatmealEngine::TextComponent>("Programming 4 Assignment", font));
	go->GetTransform().SetPosition(80, 20);
	Add(go);

	font = OatmealEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<OatmealEngine::GameObject>();
	auto fpsComp{std::make_shared<OatmealEngine::FPSComponent>(font, SDL_Color{255,255,0})};
	go->AddComponenet(fpsComp);
	fpsComp->Init();
	Add(go);
}
