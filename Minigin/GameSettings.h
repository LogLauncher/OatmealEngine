#pragma once

namespace OatmealEngine
{
	class GameSettings
	{
	public:
		struct WindowDetails
		{
			WindowDetails()
				: WindowDetails(1280, 720)
			{}
			WindowDetails(int width, int height)
				: Width{width}
				, Height{height}
				, VSync{true}
			{}

			int Width;
			int Height;
			bool VSync;
		};

		explicit GameSettings() = default;
		~GameSettings() = default;

		static WindowDetails WindowSettings;
		static glm::vec2 Gravity;
	};

	__declspec(selectany) OatmealEngine::GameSettings::WindowDetails GameSettings::WindowSettings{};
	__declspec(selectany) glm::vec2 GameSettings::Gravity{0, 150.f};

}