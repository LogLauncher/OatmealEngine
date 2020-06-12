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
		static float Gravity;
	};

	__declspec(selectany) OatmealEngine::GameSettings::WindowDetails GameSettings::WindowSettings{};
	__declspec(selectany) float GameSettings::Gravity{9.81f};

}