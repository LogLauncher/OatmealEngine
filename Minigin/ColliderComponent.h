#pragma once
#include "BaseCollider.h"

namespace OatmealEngine
{
	class ColliderComponent final : public BaseCollider
	{
	public:
		explicit ColliderComponent(int width, int height);
		explicit ColliderComponent(const SDL_Point& size);
		virtual ~ColliderComponent() = default;
		DEL_ROF(ColliderComponent);

		virtual void LateUpdate() override;
		virtual void Start() override;

		virtual bool CheckCollision(RigidbodyComponent* pSelfRigidbody, std::shared_ptr<RigidbodyComponent> pOther) override;

	};
}

