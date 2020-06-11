#pragma once
#include "BaseComponent.h"
#include "SDL_pixels.h"

namespace OatmealEngine
{
	class Font;
	class Texture2D;

	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::weak_ptr<Font>& font, const SDL_Color& color = {255, 255, 255});
		virtual ~TextComponent() = default;
		DEL_ROF(TextComponent);

		void UpdateTexture();

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

		virtual void Awake() override;
		virtual void LateUpdate() override;

	private:
		std::string m_Text;
		SDL_Color m_Color;
		std::weak_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
		std::weak_ptr<RenderComponent> m_pRenderComponent;

	};
	
}
