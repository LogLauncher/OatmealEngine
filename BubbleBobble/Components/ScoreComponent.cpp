#include "MiniginPCH.h"
#include "ScoreComponent.h"

#include "GameTime.h"
#include "GameObject.h"

using namespace OatmealEngine;

ScoreComponent::ScoreComponent()
	: m_LifeTime{.75f}
	, m_Timer{0}
{}

void ScoreComponent::Update()
{
	m_Timer += GameTime::GetInstance().DeltaTime();
	if (m_Timer >= m_LifeTime)
		GetGameObject().lock()->Delete();
}
