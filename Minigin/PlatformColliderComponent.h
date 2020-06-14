#pragma once
#include "BaseCollider.h"

namespace OatmealEngine
{
	class PlatformColliderComponent final : public BaseCollider
	{
	public:
		explicit PlatformColliderComponent(int width, int height);
		explicit PlatformColliderComponent(const SDL_Point& size);
		virtual ~PlatformColliderComponent() = default;
		DEL_ROF(PlatformColliderComponent);

		virtual void CollidedLogic(std::shared_ptr<RigidbodyComponent> pOtherRigidbody, const SDL_Rect& intersectionRect) override;

	};

}
