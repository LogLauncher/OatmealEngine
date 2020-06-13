#pragma once
#include "BaseComponent.h"
#include "SDL_rect.h"

namespace OatmealEngine
{
	class Texture2D;
	class RenderComponent;

	class SpriteComponent final : public BaseComponent
	{
	public:
		explicit SpriteComponent(const std::weak_ptr<Texture2D>& pTexture);
		explicit SpriteComponent(const std::weak_ptr<Texture2D>& pTexture, const SDL_Point& size, int row, int column);
		virtual ~SpriteComponent() = default;
		DEL_ROF(SpriteComponent);

		virtual void Awake() override;
		virtual void LateUpdate() override;

		const SDL_Point& GetSize() const { return m_TileSize; }
		void SetRowColumn(int row, int col);

	private:
		std::weak_ptr<Texture2D> m_pTexture;
		std::weak_ptr<RenderComponent> m_pRenderComponent;

		const SDL_Point m_TileSize;
		int m_Row;
		int m_Column;

	};

}
