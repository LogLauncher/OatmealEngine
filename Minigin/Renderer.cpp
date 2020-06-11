#include "MiniginPCH.h"
#include <SDL.h>

#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "SDL_rect.h"

void OatmealEngine::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void OatmealEngine::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().RootRender();
	
	SDL_RenderPresent(m_Renderer);
}

void OatmealEngine::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void OatmealEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void OatmealEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	RenderTexture(texture, x, y, width, height, 0);
}

void OatmealEngine::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float angle) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(abs(width));
	dst.h = static_cast<int>(abs(height));
	SDL_Point center;
	center.x = static_cast<int>(abs(width) / 2.f);
	center.y = static_cast<int>(abs(height) / 2.f);

	// #TODO add the srcRect
	if (width >= 0 && height >= 0)
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_NONE);
	else if (width < 0 && height >= 0)
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_HORIZONTAL);
	else if (width >= 0 && height < 0)
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
}

void OatmealEngine::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& destRect, float angle, const SDL_Point& direction) const
{
	SDL_Point center;
	center.x = static_cast<int>(destRect.w / 2.f);
	center.y = static_cast<int>(destRect.h / 2.f);

	// #TODO add the srcRect
	if (direction.x >= 0 && direction.y >= 0)
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &destRect, angle, &center, SDL_FLIP_NONE);
	else if (direction.x < 0 && direction.y >= 0)
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &destRect, angle, &center, SDL_FLIP_HORIZONTAL);
	else if (direction.x >= 0 && direction.y < 0)
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &destRect, angle, &center, SDL_FLIP_VERTICAL);
	else
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &destRect, angle, &center, SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
}
