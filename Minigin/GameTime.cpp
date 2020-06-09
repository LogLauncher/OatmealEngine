#include "MiniginPCH.h"
#include "GameTime.h"

const float OatmealEngine::GameTime::MsPerFixedUpdate{16 / 1000.f}; //16 for 60 fps, 33 for 30 fps (divide by 1000 to convert it to milliseconds)

void OatmealEngine::GameTime::Update()
{
	// Update the delta time
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;

	// Update the FPS
	const float oneSecond{1.f};
	m_FpsTimer += m_DeltaTime;
	++m_FpsCount;
	if (m_FpsTimer >= oneSecond)
	{
		m_FPS = m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= oneSecond;
	}
}

void OatmealEngine::GameTime::Init()
{
	m_LastTime = std::chrono::high_resolution_clock::now();
}
