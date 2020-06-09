#pragma once
#include "Singleton.h"

#include <chrono>

namespace OatmealEngine
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		void Init();

		void Update();

		float DeltaTime() const { return m_DeltaTime; }
		float FixedTime() const { return MsPerFixedUpdate; }
		int FPS() const { return m_FPS; }

	private:
		friend class Singleton<GameTime>;
		GameTime() = default;

		static const float MsPerFixedUpdate; //16 for 60 fps, 33 for 30 fps

		std::chrono::steady_clock::time_point m_LastTime;
		std::chrono::steady_clock::time_point m_CurrentTime;

		float m_DeltaTime;

		// FPS
		int m_FPS;
		int m_FpsCount;
		float m_FpsTimer;

	};

}
