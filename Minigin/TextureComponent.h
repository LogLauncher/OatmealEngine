#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(const std::string& filename);
		virtual ~TextureComponent() = default;
		DEL_ROF(TextureComponent);

		void Render() const override;

		const glm::vec2& GetSize() { return m_Size; }

	private:
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec2 m_Size;

	};

}
