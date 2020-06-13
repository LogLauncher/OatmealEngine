#include "MiniginPCH.h"
#include "RigidbodyComponent.h"

#include "GameTime.h"
#include "ColliderComponent.h"

OatmealEngine::RigidbodyComponent::RigidbodyComponent(const std::weak_ptr<ColliderComponent>& pColliderComponent)
	: RigidbodyComponent(pColliderComponent, false)
{}

OatmealEngine::RigidbodyComponent::RigidbodyComponent(const std::weak_ptr<ColliderComponent>& pColliderComponent, bool isStatic)
	: m_pCollider{pColliderComponent}
	, m_Velocity{0,0}
	, m_HasGravity{true}
	, m_IsStatic{isStatic}
	, m_IsGrounded{false}
{}

void OatmealEngine::RigidbodyComponent::FixedUpdate()
{
	if (!m_IsStatic)
	{
		const auto& gameTime{GameTime::GetInstance()};
		auto& transform{GetTransform()};
		transform.Translate(glm::vec3(m_Velocity.x, m_Velocity.y, 0) * gameTime.FixedTime());

		m_Velocity += GameSettings::Gravity * gameTime.FixedTime();
	}
}

void OatmealEngine::RigidbodyComponent::UpdateCollision(const std::vector<std::weak_ptr<RigidbodyComponent>>& pRigidbodyComponents)
{
	auto pCollider{m_pCollider.lock()};
	for (const auto& pOtherRigidbody : pRigidbodyComponents)
	{
		auto pSharedRigidbody{pOtherRigidbody.lock()};
		SDL_Rect intersectionRect{};
		auto selfRect{pCollider->GetRect()};
		auto otherRect{pSharedRigidbody->GetCollider().lock()->GetRect()};
		
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
					m_Velocity.x = 0;
				}
				else if (intersectionRect.h < intersectionRect.w)
				{
					GetTransform().Translate(0, int(intersectionRect.h * Utils::Sign(moveOut.y)));
					if (m_Velocity.y > 0)
						m_IsGrounded = true;
					m_Velocity.y = 0;
				}
			}
		}
	}
}
