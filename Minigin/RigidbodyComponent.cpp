#include "MiniginPCH.h"
#include "RigidbodyComponent.h"

#include "GameTime.h"
#include "ColliderComponent.h"

OatmealEngine::RigidbodyComponent::RigidbodyComponent(const std::weak_ptr<BaseCollider>& pColliderComponent)
	: RigidbodyComponent(pColliderComponent, false)
{}

OatmealEngine::RigidbodyComponent::RigidbodyComponent(const std::weak_ptr<BaseCollider>& pColliderComponent, bool isStatic)
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
		pCollider->CheckCollision(this, pOtherRigidbody.lock());
}
