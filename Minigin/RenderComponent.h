#pragma once
#include "BaseComponent.h"
#include "Renderer.h"

namespace OatmealEngine
{
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent() = default;

		void SetTexture(std::weak_ptr<Texture2D> texture);
		void Render() const;

	private:
		std::weak_ptr<Texture2D> m_Texture;

	};

}
