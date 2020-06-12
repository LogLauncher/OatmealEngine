#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class ColliderComponent;

	class RigidbodyComponent final : public BaseComponent
	{
	public:
		explicit RigidbodyComponent(const std::weak_ptr<ColliderComponent>& pColliderComponent);
		explicit RigidbodyComponent(const std::weak_ptr<ColliderComponent>& pColliderComponent, bool isStatic);
		virtual ~RigidbodyComponent() = default;

		virtual void FixedUpdate() override;

		std::weak_ptr<ColliderComponent> GetCollider() const { return m_pCollider; }
		void UpdateCollision(const std::vector<std::weak_ptr<RigidbodyComponent>>& pRigidbodyComponents);

		void AddForce(const glm::vec2& force) { m_Velocity += force; }
		void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; }
		const glm::vec2& GetVelocity() const { return m_Velocity; }

		void EnableGravity(bool hasGravity) { m_HasGravity = hasGravity; }
		
		bool IsStatic() const { return m_IsStatic; }

	private:
		glm::vec2 m_Velocity;
		std::weak_ptr<ColliderComponent> m_pCollider;

		bool m_HasGravity;
		bool m_IsStatic;

	};
}
