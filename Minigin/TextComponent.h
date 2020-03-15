#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextComponent() = default;

		void Update(float deltaTime) override;
		void Render() const override;
		void UpdateTexture();

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		SDL_Color m_Color;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;

	};
	
}
