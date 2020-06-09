#include "MiniginPCH.h"
#include <SDL_pixels.h>

#include "FPSComponent.h"

OatmealEngine::FPSComponent::FPSComponent(const std::shared_ptr<Font>& font, const SDL_Color& color)
	: m_FPS{0}
	, m_FpsCount{0}
	, m_FpsTimer{0}
	, m_TextComponent{"00 FPS", font, color}
{}

void OatmealEngine::FPSComponent::Init()
{
	m_TextComponent.SetGameObject(GetGameObject());
}

void OatmealEngine::FPSComponent::Update()
{
	m_FpsTimer += 0.016f;
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

void OatmealEngine::FPSComponent::Render() const
{
	m_TextComponent.Render();
}
