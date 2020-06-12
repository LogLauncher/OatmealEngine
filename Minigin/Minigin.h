#pragma once

struct SDL_Window;

namespace OatmealEngine
{
	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();

	private:
		SDL_Window* m_Window{};
	};
}