#include "MiniginPCH.h"
#include "RenderComponent.h"

#include "Texture2D.h"

OatmealEngine::RenderComponent::RenderComponent()
	: m_pTexture{}
	, m_SrcRect{-1,-1,-1,-1}
	, m_DestRect{-1,-1,-1,-1}
	, m_Direction{1,1}
{}

void OatmealEngine::RenderComponent::Render() const
{
	if (!m_pTexture.expired())
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture.lock(), m_SrcRect, m_DestRect, GetTransform().GetRotation(), m_Direction);
	}
}

void OatmealEngine::RenderComponent::SetTexture(const std::weak_ptr<Texture2D>& texture, bool fullTexture)
{
	m_pTexture = texture;
	if (fullTexture)
	{
		auto& transform{GetTransform()};
		const auto& size{m_pTexture.lock()->GetSize()};
		SDL_Rect srcRect{};
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = size.x;
		srcRect.h = size.y;
		SetSrcRect(srcRect);

		const auto& pos{transform.GetPosition()};
		const auto& scale{transform.GetScale()};
		SDL_Rect destRect{};
		destRect.x = int(pos.x);
		destRect.y = int(pos.y);
		destRect.w = int(abs(size.x * scale.x));
		destRect.h = int(abs(size.y * scale.y));
		SetDestRect(destRect);
	}
}
