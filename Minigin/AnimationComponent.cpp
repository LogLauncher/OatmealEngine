#include "MiniginPCH.h"
#include "AnimationComponent.h"

#include "GameTime.h"
#include "GameObject.h"
#include "SpriteComponent.h"

OatmealEngine::AnimationComponent::AnimationComponent()
	: m_Animations{}
	, m_pSpriteComponent{}
	, m_CurrentAnimationName{0}
	, m_ActiveAnimationDesc{-1,-1,0}
	, m_Timer{}
	, m_CurrentFrame{0}
	, m_CurrentAnimation{}
{}

void OatmealEngine::AnimationComponent::Start()
{
	m_pSpriteComponent = GetGameObject().lock()->GetComponent<SpriteComponent>();
}

void OatmealEngine::AnimationComponent::LateUpdate()
{
	if (!m_CurrentAnimation.empty())
	{
		m_Timer += GameTime::GetInstance().DeltaTime();
		if (m_ActiveAnimationDesc.Duration > 0 && m_Timer >= m_ActiveAnimationDesc.Duration)
		{
			m_Timer -= m_ActiveAnimationDesc.Duration;
			m_pSpriteComponent.lock()->SetRowColumn(m_ActiveAnimationDesc.Row, m_ActiveAnimationDesc.Column);

			m_CurrentFrame = ++m_CurrentFrame % m_CurrentAnimation.size();
			m_ActiveAnimationDesc = m_CurrentAnimation[m_CurrentFrame];
		}
	}
}

bool OatmealEngine::AnimationComponent::AddAnimation(const std::string& name, const std::vector<FrameDesc>& animations)
{
	size_t nameHash = std::hash<std::string>{}(name);
	auto it{m_Animations.find(nameHash)};
	if (it != m_Animations.end())
		return false;

	m_Animations.insert(std::make_pair(nameHash, animations));

	return true;
}

bool OatmealEngine::AnimationComponent::Play(const std::string& name)
{
	size_t nameHash = std::hash<std::string>{}(name);
	if (m_CurrentAnimationName != nameHash)
	{
		auto it{m_Animations.find(nameHash)};
		if (it == m_Animations.end())
			return false;

		m_CurrentAnimationName = nameHash;

		m_CurrentFrame = 0;
		m_Timer = 0;

		m_CurrentAnimation = (*it).second;

		m_ActiveAnimationDesc = m_CurrentAnimation[m_CurrentFrame];
		m_pSpriteComponent.lock()->SetRowColumn(m_ActiveAnimationDesc.Row, m_ActiveAnimationDesc.Column);

		return true;

	}

	return false;
}
