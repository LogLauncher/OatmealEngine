#pragma once
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

		SDL_Texture* GetSDLTexture() const;
		glm::vec2 GetSize() const;

	private:
		SDL_Texture* m_Texture;
		glm::vec2 m_Size;

	};
}
