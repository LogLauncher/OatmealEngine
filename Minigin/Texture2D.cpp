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

OatmealEngine::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
