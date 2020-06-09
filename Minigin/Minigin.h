#pragma once

struct SDL_Window;

namespace OatmealEngine
{
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

		void SetWindowDimentions(int width, int height) {
			m_WindowWidth = width;
			m_WindowHeight = height;
		}

	private:
		SDL_Window* m_Window{};
		int m_WindowWidth;
		int m_WindowHeight;
	};
}