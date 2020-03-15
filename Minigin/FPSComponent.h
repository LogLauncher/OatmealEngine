#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(const std::shared_ptr<Font>& font, const SDL_Color& color = {255,255,255});
		virtual ~FPSComponent() = default;

		void Init();

		void Update(float deltaTime) override;
		void Render() const override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

	private:
		TextComponent m_TextComponent;

		float m_FpsTimer;
		int m_FpsCount;
		int m_FPS;

	};

}

