#include "MiniginPCH.h"
#include "Prefabs.h"

#include "BaseScene.h"
#include "Components.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "../Components/BubbleComponent.h"
#include "../Components/Enemies/ZenChanEnemyComponent.h"

using namespace OatmealEngine;

std::shared_ptr<OatmealEngine::GameObject> Prefabs::Bubble(const glm::vec3& position, int directionX, int animationStartCol)
{
	auto pScene{SceneManager::GetInstance().GetActiveScene().lock()};
	auto go{pScene->NewGameObject()};
	go->SetTag("Bubble");

	go->AddComponent(std::make_shared<SpriteComponent>(ResourceManager::GetInstance().LoadTexture("Misc"), SDL_Point{16,16}, 0, animationStartCol));
	
	auto pCollider = go->AddComponent(std::make_shared<ColliderComponent>(16, 16));
	pCollider->EnableTrigger(true);

	auto pRigidbody{go->AddComponent(std::make_shared<RigidbodyComponent>(pCollider))};
	pRigidbody->SetKinematic(true);

	auto pAnimation{go->AddComponent(std::make_shared<AnimationComponent>())};
	pAnimation->AddAnimation("Idle",
		{
			AnimationComponent::FrameDesc(0, animationStartCol, .1f),
			AnimationComponent::FrameDesc(0, animationStartCol + 1, .1f),
		}
	);
	pAnimation->AddAnimation("Pop",
		{
			AnimationComponent::FrameDesc(0, 4, .2f),
			AnimationComponent::FrameDesc(0, 5, .2f),
			AnimationComponent::FrameDesc(0, 6, .4f),
		}
	);

	auto pBullet{go->AddComponent(std::make_shared<BubbleComponent>(directionX))};
	pCollider->SetOnTriggerCallback(std::bind(&BubbleComponent::OnTrigger, pBullet, std::placeholders::_1));
	go->GetTransform().SetPosition(position);

	return go;
}
std::shared_ptr<OatmealEngine::GameObject> Prefabs::ZenChan(const glm::vec3& position)
{
	auto pScene{SceneManager::GetInstance().GetActiveScene().lock()};
	auto go{pScene->NewGameObject()};
	go->SetTag("Enemy");

	go->AddComponent(std::make_shared<SpriteComponent>(ResourceManager::GetInstance().LoadTexture("Characters"), SDL_Point{16,16}, 6, 0));

	auto pCollider = go->AddComponent(std::make_shared<ColliderComponent>(16, 16));

	auto pRigidbody{go->AddComponent(std::make_shared<RigidbodyComponent>(pCollider))};

	auto pAnimation{go->AddComponent(std::make_shared<AnimationComponent>())};
	pAnimation->AddAnimation("Idle",
		{
			AnimationComponent::FrameDesc(6, 0, -1),
		}
	);
	pAnimation->AddAnimation("Move",
		{
			AnimationComponent::FrameDesc(6, 0, .1f),
			AnimationComponent::FrameDesc(6, 1, .1f),
			AnimationComponent::FrameDesc(6, 2, .1f),
			AnimationComponent::FrameDesc(6, 3, .1f),
		}
	);
	pAnimation->AddAnimation("Hit",
		{
			AnimationComponent::FrameDesc(6, 4, .1f),
			AnimationComponent::FrameDesc(6, 5, .1f),
			AnimationComponent::FrameDesc(6, 6, .1f),
			AnimationComponent::FrameDesc(6, 7, .1f),
		}
	);

	auto pEnemy{go->AddComponent(std::make_shared<ZenChanEnemyComponent>())};
	pCollider->SetOnCollideCallback(std::bind(&ZenChanEnemyComponent::OnCollide, pEnemy, std::placeholders::_1));
	go->GetTransform().SetPosition(position);

	return go;
}
