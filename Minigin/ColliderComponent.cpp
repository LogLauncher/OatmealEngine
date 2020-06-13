#include "MiniginPCH.h"
#include "ColliderComponent.h"

#include "GameTime.h"
#include "RigidbodyComponent.h"

OatmealEngine::ColliderComponent::ColliderComponent(int width, int height)
	: ColliderComponent(SDL_Point{width, height})
{}

OatmealEngine::ColliderComponent::ColliderComponent(const SDL_Point& size)
	: BaseCollider(size)
{}

void OatmealEngine::ColliderComponent::CollidedLogic(RigidbodyComponent* pOtherRigidbody, const SDL_Rect& intersectionRect)
{
	EjectFromCollider(pOtherRigidbody, intersectionRect);
}
