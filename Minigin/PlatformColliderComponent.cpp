#include "MiniginPCH.h"
#include "PlatformColliderComponent.h"

#include "GameObject.h"
#include "RigidbodyComponent.h"

OatmealEngine::PlatformColliderComponent::PlatformColliderComponent(int width, int height)
	: PlatformColliderComponent(SDL_Point{width, height})
{}

OatmealEngine::PlatformColliderComponent::PlatformColliderComponent(const SDL_Point& size)
	: BaseCollider(size)
{}

void OatmealEngine::PlatformColliderComponent::CollidedLogic(std::shared_ptr<RigidbodyComponent> pOtherRigidbody, const SDL_Rect& intersectionRect)
{
	if (pOtherRigidbody->GetVelocity().y <= 0.001f)
		return;

	EjectFromCollider(pOtherRigidbody, intersectionRect);
}
