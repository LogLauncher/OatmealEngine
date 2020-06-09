#include "MiniginPCH.h"

#include <SDL_pixels.h>

#include "FPSComponent.h"
#include "GameTime.h"
#include "GameObject.h"

OatmealEngine::FPSComponent::FPSComponent(const std::shared_ptr<Font>& font, const SDL_Color& color)
	: m_Font{font}
	, m_Color{color}
{}

void OatmealEngine::FPSComponent::Awake()
{
	m_TextComponent = std::make_shared<TextComponent>("00 FPS", m_Font, m_Color);
	GetGameObject().lock()->AddComponenet(m_TextComponent);
}

void OatmealEngine::FPSComponent::Update()
{
	std::stringstream sst{};
	sst << GameTime::GetInstance().FPS() << " FPS";
	m_TextComponent->SetText(sst.str());
}
