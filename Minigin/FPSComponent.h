#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace OatmealEngine
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(const std::shared_ptr<Font>& font, const SDL_Color& color = {255,255,255});
		virtual ~FPSComponent() = default;
		DEL_ROF(FPSComponent);

		void Init();

		void Update() override;
		void Render() const override;


	private:
		TextComponent m_TextComponent;

	};

}

