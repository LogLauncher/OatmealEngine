#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color = {255, 255, 255});
		virtual ~TextComponent() = default;
		DEL_ROF(TextComponent);

		void Render() const override;
		void UpdateTexture();

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

	private:
		std::string m_Text;
		SDL_Color m_Color;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;

	};
	
}
