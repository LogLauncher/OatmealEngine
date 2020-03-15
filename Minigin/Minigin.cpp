#include "MiniginPCH.h"
#include "Minigin.h"

#include <SDL.h>
#include <chrono>
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"

using namespace std::chrono;

const float dae::Minigin::MsPerFrame{16 / 1000.f}; //16 for 60 fps, 33 for 30 fps (divide by 1000 to convert it to milliseconds)

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go{std::make_shared<GameObject>()};
	go->AddComponenet(std::make_shared<TextureComponent>("background.jpg"));
	scene->Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponenet(std::make_shared<TextureComponent>("logo.png"));
	go->GetTransform().SetPosition(216, 180);
	scene->Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponenet(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	go->GetTransform().SetPosition(80, 20);
	scene->Add(go);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime{high_resolution_clock::now()};
		float lag{};
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime{duration<float>(currentTime - lastTime).count()};
			lastTime = currentTime;
			lag += deltaTime;

			doContinue = input.ProcessInput();
			while (lag >= MsPerFrame)
			{
				sceneManager.Update(MsPerFrame);
				lag -= MsPerFrame;
			}
			renderer.Render();
			
		}
	}

	Cleanup();
}
