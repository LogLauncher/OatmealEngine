#pragma once
#include "BaseComponent.h"

#include "Renderer.h"
#include "SDL_rect.h"

namespace OatmealEngine
{
	class RenderComponent final : public BaseComponent
	{
	public:
		explicit RenderComponent();

		void SetTexture(const std::weak_ptr<Texture2D>& texture, bool fullTexture = true);
		void SetSrcRect(const SDL_Rect& rect) { m_SrcRect = rect; }
		void SetDestRect(const SDL_Rect& rect) { m_DestRect = rect; }
		void SetDirection(const SDL_Point& point) { m_Direction = point; }

		void Render() const;

	private:
		std::weak_ptr<Texture2D> m_pTexture;
		SDL_Rect m_SrcRect;
		SDL_Rect m_DestRect;
		SDL_Point m_Direction;

	};

}
