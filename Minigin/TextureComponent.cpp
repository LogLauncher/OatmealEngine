#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Renderer.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "SDL_render.h"

OatmealEngine::TextureComponent::TextureComponent(const std::string& filename)
	: m_Texture{ResourceManager::GetInstance().LoadTexture(filename)}
	, m_Size{}
{
	int width{}, height{};
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &width, &height);
	m_Size.x = float(width);
	m_Size.y = float(height);
}

void OatmealEngine::TextureComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& transform{GetGameObject().lock()->GetTransform()};
		const auto& pos{transform.GetPosition()};
		const auto& scale{transform.GetScale()};
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Size.x * scale.x, m_Size.y * scale.y, transform.GetRotation());
	}
}