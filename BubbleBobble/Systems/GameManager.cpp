#include "MiniginPCH.h"
#include "GameManager.h"

#include "Prefabs.h"
#include "GameTime.h"
#include "BaseScene.h"
#include "Components.h"
#include "GameObject.h"
#include "LevelBuilder.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "../Components/PlayerComponent.h"

using namespace OatmealEngine;

GameManager::GameManager()
	: m_LevelID{1}
	, m_IsInitialized{false}
	, m_SecondPlayer{false}
	, m_State{State::MENU}
	, m_TimeBeforeLevelSwitch{5.f}
	, m_TimerSwitchLevel{0}
{}

void GameManager::Initialize()
{
	if (!m_IsInitialized)
	{
		InputManager::GetInstance().AddInputAction(InputAction("Join", InputTriggerState::Pressed, SDLK_j, GamepadButton::START, PlayerIndex::PlayerTwo));
#ifdef _DEBUG
		InputManager::GetInstance().AddInputAction(InputAction("NextLevel", InputTriggerState::Pressed, SDLK_F2));
		InputManager::GetInstance().AddInputAction(InputAction("PrevLevel", InputTriggerState::Pressed, SDLK_F1));
#endif // _DEBUG

		m_IsInitialized = true;
	}
}

void GameManager::Update()
{
	switch (m_State)
	{
	case State::MENU:
		break;
	case State::GAME:
		
		// Check input
		auto& inputManager{InputManager::GetInstance()};
		if (!m_SecondPlayer && inputManager.IsActionTriggered("Join", PlayerIndex::PlayerTwo))
			AddSecondPlayer();

#ifdef _DEBUG
		if (inputManager.IsActionTriggered("NextLevel", PlayerIndex::PlayerOne))
		{
			++m_LevelID;
			ClampRef(m_LevelID, 1, 100);
			LoadLevel();
		}
		if (inputManager.IsActionTriggered("PrevLevel", PlayerIndex::PlayerOne))
		{
			--m_LevelID;
			ClampRef(m_LevelID, 1, 100);
			LoadLevel();
		}
#endif // _DEBUG

		// Check is can go to next level
		if (m_pEnemies.empty())
		{
			m_TimerSwitchLevel += GameTime::GetInstance().DeltaTime();
			if (m_TimerSwitchLevel >= m_TimeBeforeLevelSwitch)
			{
				m_TimerSwitchLevel = 0;
				++m_LevelID;
				ClampRef(m_LevelID, 1, 100);
				LoadLevel(); 
			}
		}

		break;
	}

}

void GameManager::AddSecondPlayer()
{
	auto go = SceneManager::GetInstance().GetActiveScene().lock()->NewGameObject();
	go->SetTag("Player");
	go->AddComponent(std::make_shared<SpriteComponent>(ResourceManager::GetInstance().LoadTexture("Characters"), SDL_Point{16, 16}, 3, 0));
	go->AddComponent(std::make_shared<PlayerComponent>(PlayerIndex::PlayerTwo));

	auto collider = go->AddComponent(std::make_shared<ColliderComponent>(16, 16));
	go->AddComponent(std::make_shared<RigidbodyComponent>(collider));

	auto animation = go->AddComponent(std::make_shared<AnimationComponent>());
	animation->AddAnimation("Idle",
		{
			AnimationComponent::FrameDesc(3,0,-1),
		}
	);
	animation->AddAnimation("Move",
		{
			AnimationComponent::FrameDesc(3,0,.05f),
			AnimationComponent::FrameDesc(3,1,.05f),
			AnimationComponent::FrameDesc(3,2,.05f),
			AnimationComponent::FrameDesc(3,3,.05f),
			AnimationComponent::FrameDesc(3,4,.05f),
			AnimationComponent::FrameDesc(3,5,.05f),
			AnimationComponent::FrameDesc(3,6,.05f),
			AnimationComponent::FrameDesc(3,7,.05f),
		}
	);
	animation->AddAnimation("Shoot",
		{
			AnimationComponent::FrameDesc(4, 0, .1f),
			AnimationComponent::FrameDesc(4, 4, .1f),
			AnimationComponent::FrameDesc(4, 0, .1f),
		}
	);
	animation->AddAnimation("Hit",
		{
			AnimationComponent::FrameDesc(5,0,.075f),
			AnimationComponent::FrameDesc(5,1,.075f),
			AnimationComponent::FrameDesc(5,2,.075f),
			AnimationComponent::FrameDesc(5,3,.075f),
		}
	);
	go->GetTransform().SetPosition(8 * GameSettings::GlobalScale * 26, 500);
	go->GetTransform().SetScale(-1, 1);
	m_SecondPlayer = true;
}

void GameManager::LoadLevel()
{
	for (const auto& pObject : m_pLevelBlocks)
		pObject.lock()->Delete();

	m_pLevelBlocks.clear();

	LevelBuilder::Build(m_LevelID, SceneManager::GetInstance().GetActiveScene().lock(), ResourceManager::GetInstance().LoadTexture("Blocks").lock(), m_pLevelBlocks);

	m_pEnemies.push_back(Prefabs::ZenChan({17 * GameSettings::GlobalScale * 8, 2 * GameSettings::GlobalScale * 8, 0}));
}
