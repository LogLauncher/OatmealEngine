#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "SDL_render.h"

OatmealEngine::ColliderComponent::ColliderComponent(int width, int height)
	: m_OriginalSize{width, height}
	, m_Size{width, height}
{}

void OatmealEngine::ColliderComponent::Start()
{
	UpdateSize();
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
	SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(sdlRenderer, &dest);
}
#endif // _DEBUG

void OatmealEngine::ColliderComponent::LateUpdate()
{
	UpdateSize();
}

void OatmealEngine::ColliderComponent::UpdateSize()
{
	auto& transform{GetTransform()};
	m_Size.x = int(m_OriginalSize.x * transform.GetScale().x);
	m_Size.y = int(m_OriginalSize.y * transform.GetScale().y);
}
