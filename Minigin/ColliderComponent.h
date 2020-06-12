#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class ColliderComponent final : public BaseComponent
	{
	public:
		explicit ColliderComponent(int width, int height);
		explicit ColliderComponent(const SDL_Point& size);
		virtual ~ColliderComponent() = default;
		DEL_ROF(ColliderComponent);

		virtual void LateUpdate() override;
		virtual void Start() override;
#ifdef _DEBUG
		virtual void DebugRender() override;
#endif // _DEBUG

		const SDL_Point& GetSize() const { return m_Size; }
		SDL_Rect GetRect() const;

		const bool IsTrigger() const { return m_IsTrigger; }
		void EnableTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }

	private:
		SDL_Point m_OriginalSize;
		SDL_Point m_Size;

		bool m_IsTrigger;

		void UpdateSize();
	};
}

