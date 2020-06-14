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

		virtual void CollidedLogic(std::shared_ptr<RigidbodyComponent> pOtherRigidbody, const SDL_Rect& intersectionRect) override;

	};
}

