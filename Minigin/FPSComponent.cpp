#include "MiniginPCH.h"

#include <SDL_pixels.h>

#include "GameTime.h"
#include "GameObject.h"
#include "FPSComponent.h"

OatmealEngine::FPSComponent::FPSComponent(const std::weak_ptr<Font>& pFont, const SDL_Color& color)
	: m_pFont{pFont}
	, m_Color{color}
{}

void OatmealEngine::FPSComponent::Awake()
{
	auto pTextComponent{std::make_shared<TextComponent>("00 FPS", m_pFont, m_Color)};
	GetGameObject().lock()->AddComponent(pTextComponent);
	m_pTextComponent = pTextComponent;
}

void OatmealEngine::FPSComponent::Update()
{
	std::stringstream sst{};
	sst << GameTime::GetInstance().FPS() << " FPS";
	m_pTextComponent.lock()->SetText(sst.str());
}
