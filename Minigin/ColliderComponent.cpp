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

void OatmealEngine::ColliderComponent::Start()
{
	UpdateSize();
}

void OatmealEngine::ColliderComponent::LateUpdate()
{
	UpdateSize();
}

bool OatmealEngine::ColliderComponent::CheckCollision(RigidbodyComponent* pSelfRigidbody, std::shared_ptr<RigidbodyComponent> pOtherRigidbody)
{
	SDL_Rect intersectionRect{};
	auto selfRect{GetRect()};
	auto otherRect{pOtherRigidbody->GetCollider().lock()->GetRect()};

	// Don't check with self
	if (!SDL_RectEquals(&selfRect, &otherRect))
	{
		// Check if intersecting
		if (SDL_IntersectRect(&selfRect, &otherRect, &intersectionRect))
		{
			auto& pos{GetTransform().GetPosition()};
			const glm::vec3 otherPos{intersectionRect.x, intersectionRect.y, 0};
			const glm::vec3 moveOut{pos - otherPos};

			// Prioritize X axis
			if (abs(moveOut.x) > abs(moveOut.y) && intersectionRect.w < intersectionRect.h)
			{
				GetTransform().Translate(int(intersectionRect.w * Utils::Sign(moveOut.x)), 0);
				pSelfRigidbody->ResetVelocityX();
			}
			else if (intersectionRect.h < intersectionRect.w)
			{
				GetTransform().Translate(0, int(intersectionRect.h * Utils::Sign(moveOut.y)));
				if (pSelfRigidbody->GetVelocity().y > 0)
					pSelfRigidbody->SetGrounded(true);
				pSelfRigidbody->ResetVelocityY();

			}

			return true;
		}
	}
	return false;
}
