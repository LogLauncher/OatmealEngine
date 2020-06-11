#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

OatmealEngine::Texture2D::Texture2D(SDL_Texture* texture)
	: m_pTexture{texture}
{
	int width{}, height{};
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &width, &height);
	m_Size.x = width;
	m_Size.y = height;
}

OatmealEngine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}
