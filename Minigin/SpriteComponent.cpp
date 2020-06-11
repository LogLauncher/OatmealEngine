#include "MiniginPCH.h"
#include "SpriteComponent.h"

#include "Texture2D.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "RenderComponent.h"

OatmealEngine::SpriteComponent::SpriteComponent(const std::weak_ptr<Texture2D>& pTexture)
	: SpriteComponent(pTexture, pTexture.lock()->GetSize(),-1,-1)
{}

OatmealEngine::SpriteComponent::SpriteComponent(const std::weak_ptr<Texture2D>& pTexture, const SDL_Point& size, int row, int column)
	: m_pTexture{pTexture}
	, m_TileSize{size}
	, m_Row{row}
	, m_Column{column}
{}

void OatmealEngine::SpriteComponent::Awake()
{
	auto pRenderComponent{std::make_shared<RenderComponent>()};
	pRenderComponent->SetTexture(m_pTexture, false);

	SDL_Rect srcRect{};
	srcRect.x = (m_Column < 0) ? 0 : m_TileSize.x * m_Column;
	srcRect.y = (m_Row < 0) ? 0 : m_TileSize.y * m_Row;
	srcRect.w = m_TileSize.x;
	srcRect.h = m_TileSize.y;
	pRenderComponent->SetSrcRect(srcRect);

	auto& transform{GetTransform()};
	const auto& pos{transform.GetPosition()};
	const auto& scale{transform.GetScale()};
	SDL_Rect destRect{};
	destRect.x = int(pos.x);
	destRect.y = int(pos.y);
	destRect.w = int(abs(m_TileSize.x * scale.x));
	destRect.h = int(abs(m_TileSize.y * scale.y));
	pRenderComponent->SetDestRect(destRect);

	GetGameObject().lock()->AddComponent(pRenderComponent);
	m_pRenderComponent = pRenderComponent;
}

void OatmealEngine::SpriteComponent::LateUpdate()
{
	auto& transform{GetTransform()};
	const auto& pos{transform.GetPosition()};
	const auto& scale{transform.GetScale()};

	SDL_Rect destRect{};
	destRect.x = int(pos.x);
	destRect.y = int(pos.y);
	destRect.w = int(abs(m_TileSize.x * scale.x));
	destRect.h = int(abs(m_TileSize.y * scale.y));

	auto pRenderComponent{m_pRenderComponent.lock()};
	pRenderComponent->SetDestRect(destRect);

	SDL_Point direction{};
	direction.x = int(Utils::Sign(scale.x));
	direction.y = int(Utils::Sign(scale.y));
	pRenderComponent->SetDirection(direction);

}
