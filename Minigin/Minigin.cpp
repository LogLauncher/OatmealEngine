#include "MiniginPCH.h"
#include "Minigin.h"

#include <SDL.h>
#include <thread>

#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "BaseScene.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "GameTime.h"

void OatmealEngine::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		GameSettings::WindowSettings.Width,
		GameSettings::WindowSettings.Height,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void OatmealEngine::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void OatmealEngine::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("Resources/");

	SceneManager::GetInstance().Initialize();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& gameTime = GameTime::GetInstance();

		bool doContinue = true;
		float lag{};

		gameTime.Init();

		while (doContinue)
		{
			// Update game time
			gameTime.Update();

			lag += gameTime.DeltaTime();

			doContinue = input.Update();

			while (lag >= gameTime.FixedTime())
			{
				sceneManager.RootFixedUpdate();
				lag -= gameTime.FixedTime();
			}

			sceneManager.RootUpdateCollision();

			sceneManager.RootUpdate();
			sceneManager.RootLateUpdate();

			renderer.Render();
			
		}
	}

	Cleanup();
}