#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class BaseCollider;

	class RigidbodyComponent final : public BaseComponent
	{
	public:
		explicit RigidbodyComponent(const std::weak_ptr<BaseCollider>& pColliderComponent);
		explicit RigidbodyComponent(const std::weak_ptr<BaseCollider>& pColliderComponent, bool isStatic);
		virtual ~RigidbodyComponent() = default;

		virtual void FixedUpdate() override;

		std::weak_ptr<BaseCollider> GetCollider() const { return m_pCollider; }
		void UpdateCollision(const std::vector<std::weak_ptr<RigidbodyComponent>>& pRigidbodyComponents);

		void AddForce(const glm::vec2& force) { m_Velocity += force; }
		void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; }
		void ResetVelocityX() { m_Velocity.x = 0; }
		void ResetVelocityY() { m_Velocity.y = 0; }
		const glm::vec2& GetVelocity() const { return m_Velocity; }

		void SetGrounded(bool isGrounded) { m_IsGrounded = isGrounded; }
		bool IsGrounded() { return m_IsGrounded; }

		void EnableGravity(bool hasGravity) { m_HasGravity = hasGravity; }
		
		bool IsStatic() const { return m_IsStatic; }

	private:
		glm::vec2 m_Velocity;
		std::weak_ptr<BaseCollider> m_pCollider;

		bool m_IsGrounded;

		bool m_HasGravity;
		bool m_IsStatic;

	};
}
