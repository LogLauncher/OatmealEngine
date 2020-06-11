#pragma once
#include "SDL_rect.h"

struct SDL_Texture;

namespace OatmealEngine
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D
	{
	public:	
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();
		DEL_ROF(Texture2D);

		SDL_Texture* GetSDLTexture() const { return m_pTexture; }

		const SDL_Point& GetSize() const { return m_Size; }

	private:
		SDL_Texture* m_pTexture;
		SDL_Point m_Size;

	};
}
