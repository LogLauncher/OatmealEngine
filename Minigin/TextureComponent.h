#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class Texture2D;
	class RenderComponent;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::weak_ptr<Texture2D>& pTexture);
		virtual ~TextureComponent() = default;
		DEL_ROF(TextureComponent);

		virtual void Awake() override;

	private:
		std::weak_ptr<Texture2D> m_pTexture;

	};

}
