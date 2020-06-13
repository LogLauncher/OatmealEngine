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

void OatmealEngine::PlatformColliderComponent::CollidedLogic(RigidbodyComponent* pOtherRigidbody, const SDL_Rect& intersectionRect)
{
	if (pOtherRigidbody->GetVelocity().y <= 0.001f)
		return;

	auto& pos{GetTransform().GetPosition()};
	const glm::vec3 otherPos{intersectionRect.x, intersectionRect.y, 0};
	const glm::vec3 moveOut{pos - otherPos};

	// Prioritize X axis
	if (abs(moveOut.x) > abs(moveOut.y) && intersectionRect.w < intersectionRect.h)
	{
		pOtherRigidbody->GetTransform().Translate(int(intersectionRect.w * Utils::Sign(moveOut.x)), 0);
		pOtherRigidbody->ResetVelocityX();
	}
	else if (intersectionRect.h < intersectionRect.w)
	{
		pOtherRigidbody->GetTransform().Translate(0, int(intersectionRect.h * Utils::Sign(moveOut.y)));
		if (pOtherRigidbody->GetVelocity().y > 0)
			pOtherRigidbody->SetGrounded(true);
		pOtherRigidbody->ResetVelocityY();

	}
}
