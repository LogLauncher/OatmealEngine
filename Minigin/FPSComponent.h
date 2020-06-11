#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
#include "SDL_pixels.h"

namespace OatmealEngine
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(const std::weak_ptr<Font>& pFont, const SDL_Color& color = {255,255,255});
		virtual ~FPSComponent() = default;
		DEL_ROF(FPSComponent);

		virtual void Awake() override;
		virtual void Update() override;

	private:
		std::weak_ptr<TextComponent> m_pTextComponent;
		std::weak_ptr<Font> m_pFont;
		const SDL_Color m_Color;

	};

}

