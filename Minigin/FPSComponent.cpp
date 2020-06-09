#include "MiniginPCH.h"

#include <SDL_pixels.h>

#include "FPSComponent.h"
#include "GameTime.h"

OatmealEngine::FPSComponent::FPSComponent(const std::shared_ptr<Font>& font, const SDL_Color& color)
	: m_TextComponent{"00 FPS", font, color}
{}

void OatmealEngine::FPSComponent::Init()
{
	m_TextComponent.SetGameObject(GetGameObject());
}

void OatmealEngine::FPSComponent::Update()
{
	std::stringstream sst{};
	sst << GameTime::GetInstance().FPS() << " FPS";
	m_TextComponent.SetText(sst.str());
}

void OatmealEngine::FPSComponent::Render() const
{
	m_TextComponent.Render();
}
