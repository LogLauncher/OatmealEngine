#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "SDL_pixels.h"

namespace OatmealEngine
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(const std::shared_ptr<Font>& font, const SDL_Color& color = {255,255,255});
		virtual ~FPSComponent() = default;
		DEL_ROF(FPSComponent);

		virtual void Awake() override;
		virtual void Update() override;

	private:
		std::shared_ptr<TextComponent> m_TextComponent;
		std::shared_ptr<Font> m_Font;
		const SDL_Color m_Color;

	};

}

