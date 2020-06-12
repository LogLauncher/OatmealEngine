#pragma once
#include "BaseComponent.h"

namespace OatmealEngine
{
	class ColliderComponent : public BaseComponent
	{
	public:
		explicit ColliderComponent(int width, int height);
		~ColliderComponent() = default;
		DEL_ROF(ColliderComponent);

		virtual void LateUpdate() override;
		virtual void Start() override;
#ifdef _DEBUG
		virtual void DebugRender() override;
#endif // _DEBUG

		const SDL_Point& GetSize() const { return m_Size; }

	private:
		SDL_Point m_OriginalSize;
		SDL_Point m_Size;

		void UpdateSize();
	};
}

