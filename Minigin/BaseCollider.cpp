#include "MiniginPCH.h"
#include "BaseCollider.h"

#ifdef _DEBUG
#include "Renderer.h"
#include "SDL_render.h"
#endif

#include "GameTime.h"

OatmealEngine::BaseCollider::BaseCollider(int width, int height)
	: BaseCollider(SDL_Point{width, height})
{}

void OatmealEngine::BaseCollider::Start()
{
	UpdateSize();
}

void OatmealEngine::BaseCollider::LateUpdate()
{
	UpdateSize();
}

OatmealEngine::BaseCollider::BaseCollider(const SDL_Point& size)
	: m_OriginalSize{size}
	, m_Size{size}
	, m_IsTrigger{false}
{}

void OatmealEngine::BaseCollider::UpdateSize()
{
	const auto& scale{GetTransform().GetScale()};
	m_Size.x = int(m_OriginalSize.x * abs(scale.x));
	m_Size.y = int(m_OriginalSize.y * abs(scale.y));
}

#ifdef _DEBUG
void OatmealEngine::BaseCollider::DebugRender()
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

bool OatmealEngine::BaseCollider::IsColliding(std::shared_ptr<BaseCollider> pOther, SDL_Rect& intersectionRect)
{
	auto selfRect{GetRect()};
	auto otherRect{pOther->GetRect()};

	// Don't check with self
	if (!SDL_RectEquals(&selfRect, &otherRect))
	{
		// Check if intersecting
		if (SDL_IntersectRect(&selfRect, &otherRect, &intersectionRect))
			return true;
	}
	return false;
}

SDL_Rect OatmealEngine::BaseCollider::GetRect() const
{
	SDL_Rect rect{};
	auto& pos{GetTransform().GetPosition()};
	rect.x = int(pos.x);
	rect.y = int(pos.y);
	rect.w = m_Size.x;
	rect.h = m_Size.y;
	return rect;
}
