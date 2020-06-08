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
	private:
		static const float MsPerFrame; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
	};
}