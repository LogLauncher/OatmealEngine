#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "SDL_render.h"
#include "GameTime.h"

OatmealEngine::ColliderComponent::ColliderComponent(int width, int height)
	: ColliderComponent(SDL_Point{width, height})
{}

OatmealEngine::ColliderComponent::ColliderComponent(const SDL_Point& size)
	: m_OriginalSize{size}
	, m_Size{size}
	, m_IsTrigger{false}
{}

void OatmealEngine::ColliderComponent::Start()
{
	UpdateSize();
}

void OatmealEngine::ColliderComponent::LateUpdate()
{
	UpdateSize();
}

void OatmealEngine::ColliderComponent::UpdateSize()
{
	const auto& scale{GetTransform().GetScale()};
	m_Size.x = int(m_OriginalSize.x * abs(scale.x));
	m_Size.y = int(m_OriginalSize.y * abs(scale.y));
}

#ifdef _DEBUG
void OatmealEngine::ColliderComponent::DebugRender()
{
	SDL_Renderer* sdlRenderer{Renderer::GetInstance().GetSDLRenderer()};
	SDL_Rect dest{};
	dest.x = int(GetTransform().GetPosition().x);
	dest.y = int(GetTransform().GetPosition().y);
	dest.w = m_Size.x;
	dest.h = m_Size.y;
	SDL_SetRenderDrawColor(sdlRenderer, 0, 230, 64, 255);
	SDL_RenderDrawRect(sdlRenderer, &dest);
}
#endif // _DEBUG

SDL_Rect OatmealEngine::ColliderComponent::GetRect() const
{
	SDL_Rect rect{};
	auto& pos{GetTransform().GetPosition()};
	rect.x = int(pos.x);
	rect.y = int(pos.y);
	rect.w = m_Size.x;
	rect.h = m_Size.y;
	return rect;
}
