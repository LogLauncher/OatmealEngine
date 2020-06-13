#pragma once
#include "BaseComponent.h"

#include <map>

namespace OatmealEngine
{
	class SpriteComponent;

	class AnimationComponent : public BaseComponent
	{
	public:
		struct FrameDesc
		{
			FrameDesc(int row, int col, float duration)
				: Row{row}
				, Column{col}
				, Duration{duration}
			{}

			int Row;
			int Column;
			float Duration;
		};

		explicit AnimationComponent();
		virtual ~AnimationComponent() = default;
		DEL_ROF(AnimationComponent);
		
		virtual void Start() override;
		virtual void LateUpdate() override;

		bool AddAnimation(const std::string& name, const std::vector<FrameDesc>& animations);
		bool Play(const std::string& name);

	private:
		std::map<size_t, std::vector<FrameDesc>> m_Animations;
		std::weak_ptr<SpriteComponent> m_pSpriteComponent;

		size_t m_CurrentAnimationName;
		FrameDesc m_ActiveAnimationDesc;
		float m_Timer;
		int m_CurrentFrame;
		std::vector<FrameDesc> m_CurrentAnimation;

	};

}

