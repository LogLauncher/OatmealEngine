#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>

#include "TextComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

OatmealEngine::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color)
	: m_Text{text}
	, m_Font{font}
	, m_Texture{nullptr}
	, m_Color{color}
{
	UpdateTexture();
}

void OatmealEngine::TextComponent::Update(float)
{}

void OatmealEngine::TextComponent::UpdateTexture()
{
	const SDL_Color color = m_Color;
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
	m_Texture = std::make_shared<Texture2D>(texture);
}

void OatmealEngine::TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos{GetGameObject().lock()->GetTransform().GetPosition()};
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void OatmealEngine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	UpdateTexture();
}

void OatmealEngine::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	UpdateTexture();
}
