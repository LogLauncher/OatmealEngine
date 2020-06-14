#pragma once
#include "BaseComponent.h"
#include <functional>

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

		virtual void CollidedLogic(std::shared_ptr<RigidbodyComponent> pOtherRigidbody, const SDL_Rect& intersectionRect) = 0;
		bool IsColliding(std::shared_ptr<BaseCollider> pOther, SDL_Rect& intersectionRect) const;
		void EjectFromCollider(std::shared_ptr<RigidbodyComponent> pOtherRigidbody, const SDL_Rect& intersectionRect) const;

		const SDL_Point& GetSize() const { return m_Size; }
		SDL_Rect GetRect() const;

		const bool IsTrigger() const { return m_IsTrigger; }
		void EnableTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }


		// Callbacks
		using OnCollideCallback = std::function<void(std::shared_ptr<BaseCollider> pOther)>;
		void SetOnCollideCallback(OnCollideCallback callback) { m_OnCollideCallback = callback; }

		using OnTriggerCallback = std::function<void(std::shared_ptr<BaseCollider> pOther)>;
		void SetOnTriggerCallback(OnTriggerCallback callback) { m_OnTriggerCallback = callback; }

		void CallCallbacks(std::shared_ptr<BaseCollider> pOther) const;

	protected:
		SDL_Point m_OriginalSize;
		SDL_Point m_Size;

		bool m_IsTrigger;

		OnCollideCallback m_OnCollideCallback;
		OnTriggerCallback m_OnTriggerCallback;

		void UpdateSize();
	};
}

