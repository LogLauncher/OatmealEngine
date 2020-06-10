#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>

#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "RenderComponent.h"

OatmealEngine::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color)
	: m_Text{text}
	, m_pFont{font}
	, m_pTexture{nullptr}
	, m_Color{color}
{
	UpdateTexture();
}

void OatmealEngine::TextComponent::Awake()
{
	auto pRenderComponent{std::make_shared<RenderComponent>()};
	pRenderComponent->SetTexture(m_pTexture);
	m_pRenderComponent = pRenderComponent;
	GetGameObject().lock()->AddComponent(pRenderComponent);
}

void OatmealEngine::TextComponent::UpdateTexture()
{
	const SDL_Color color = m_Color;
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTexture = std::make_shared<Texture2D>(texture);
}

void OatmealEngine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	UpdateTexture();
	m_pRenderComponent.lock()->SetTexture(m_pTexture);
}

void OatmealEngine::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	UpdateTexture();
	m_pRenderComponent.lock()->SetTexture(m_pTexture);
}
