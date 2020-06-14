#include "MiniginPCH.h"
#include "GameManagerComponent.h"

#include "BaseScene.h"
#include "Components.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Components/PlayerComponent.h"

using namespace OatmealEngine;

GameManagerComponent::GameManagerComponent()
	: m_SecondPlayer{false}
{}

void GameManagerComponent::Awake()
{
	InputManager::GetInstance().AddInputAction(InputAction("Join", InputTriggerState::Pressed, SDLK_j, GamepadButton::START, PlayerIndex::PlayerTwo));
}

void GameManagerComponent::Update()
{
	if (!m_SecondPlayer && InputManager::GetInstance().IsActionTriggered("Join", PlayerIndex::PlayerTwo))
	{
		auto go = GetGameObject().lock()->GetScene().lock()->NewGameObject();
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
}
