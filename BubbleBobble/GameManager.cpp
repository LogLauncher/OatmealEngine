#include "MiniginPCH.h"
#include "GameManager.h"

#include "BaseScene.h"
#include "Components.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Components/PlayerComponent.h"
#include "Systems/LevelBuilder.h"

using namespace OatmealEngine;

GameManager::GameManager()
	: m_LevelID{1}
	, m_IsInitialized{false}
	, m_SecondPlayer{false}
{}

void GameManager::Initialize()
{
	if (!m_IsInitialized)
	{
		InputManager::GetInstance().AddInputAction(InputAction("Join", InputTriggerState::Pressed, SDLK_j, GamepadButton::START, PlayerIndex::PlayerTwo));
		InputManager::GetInstance().AddInputAction(InputAction("NextLevel", InputTriggerState::Pressed, SDLK_F2));
		InputManager::GetInstance().AddInputAction(InputAction("PrevLevel", InputTriggerState::Pressed, SDLK_F1));

		LevelBuilder::Build(m_LevelID, SceneManager::GetInstance().GetActiveScene().lock(), ResourceManager::GetInstance().LoadTexture("Blocks").lock(), m_pLevelBlocks);

		m_IsInitialized = true;
	}
}

void GameManager::Update()
{
	auto& inputManager{InputManager::GetInstance()};
	if (!m_SecondPlayer && inputManager.IsActionTriggered("Join", PlayerIndex::PlayerTwo))
		AddSecondPlayer();
	if (inputManager.IsActionTriggered("NextLevel", PlayerIndex::PlayerOne))
		LoadLevel(++m_LevelID);
	if (inputManager.IsActionTriggered("PrevLevel", PlayerIndex::PlayerOne))
		LoadLevel(--m_LevelID);
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

void GameManager::LoadLevel(int levelID)
{
	for (const auto& pObject : m_pLevelBlocks)
		pObject.lock()->Delete();

	m_pLevelBlocks.clear();

	LevelBuilder::Build(levelID, SceneManager::GetInstance().GetActiveScene().lock(), ResourceManager::GetInstance().LoadTexture("Blocks").lock(), m_pLevelBlocks);
}
