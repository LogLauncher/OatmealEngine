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

		void Update(float deltaTime) override;
		void Render() const override;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_Texture;

	};

}
