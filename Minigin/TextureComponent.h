#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filename);
		virtual ~TextureComponent();
		DEL_RO4(TextureComponent);

		void Render() const override;

	private:
		std::shared_ptr<Texture2D> m_Texture;

	};

}
