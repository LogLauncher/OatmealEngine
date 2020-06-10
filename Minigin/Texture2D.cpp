#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

OatmealEngine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* OatmealEngine::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

glm::vec2 OatmealEngine::Texture2D::GetSize() const
{
	return m_Size;
}

OatmealEngine::Texture2D::Texture2D(SDL_Texture* texture)
	: m_Texture{texture}
{
	int width{}, height{};
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &width, &height);
	m_Size.x = float(width);
	m_Size.y = float(height);
}
