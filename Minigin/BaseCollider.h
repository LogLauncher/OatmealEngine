#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class RigidbodyComponent;

	class BaseCollider : public BaseComponent
	{
	public:
		explicit BaseCollider(int width, int height);
		explicit BaseCollider(const SDL_Point& size);
		virtual ~BaseCollider() = default;
		DEL_ROF(BaseCollider);

		virtual void Start() override;
		virtual void LateUpdate() override;
#ifdef _DEBUG
		virtual void DebugRender() override;
#endif // _DEBUG

		virtual void CollidedLogic(RigidbodyComponent* pOtherRigidbody, const SDL_Rect& intersectionRect) = 0;
		bool IsColliding(std::shared_ptr<BaseCollider> pOther, SDL_Rect& intersectionRect) const;
		void EjectFromCollider(RigidbodyComponent* pOtherRigidbody, const SDL_Rect& intersectionRect) const;

		const SDL_Point& GetSize() const {
			return m_Size;
		}
		SDL_Rect GetRect() const;

		const bool IsTrigger() const {
			return m_IsTrigger;
		}
		void EnableTrigger(bool isTrigger) {
			m_IsTrigger = isTrigger;
		}

	protected:
		SDL_Point m_OriginalSize;
		SDL_Point m_Size;

		bool m_IsTrigger;

		void UpdateSize();
	};
}

