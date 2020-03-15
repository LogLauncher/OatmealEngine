#include "MiniginPCH.h"
#include <SDL_pixels.h>

#include "FPSComponent.h"

dae::FPSComponent::FPSComponent(const std::shared_ptr<Font>& font, const SDL_Color& color)
	: m_FPS{0}
	, m_FpsCount{0}
	, m_FpsTimer{0}
	, m_TextComponent{"00 FPS", font, color}
{}

void dae::FPSComponent::Init()
{
	m_TextComponent.SetGameObject(GetGameObject());
}

void dae::FPSComponent::Update(float deltaTime)
{
	m_FpsTimer += deltaTime;
	++m_FpsCount;
	if (m_FpsTimer >= 1.0f)
	{
		m_FPS = m_FpsCount;
		m_FpsCount = 0;
		m_FpsTimer -= 1.0f;
		std::stringstream sst{};
		sst << m_FPS << " FPS";
		m_TextComponent.SetText(sst.str());
	}
}

void dae::FPSComponent::Render() const
{
	m_TextComponent.Render();
}
