#include "MiniginPCH.h"
#include "Prefabs.h"

#include "BaseScene.h"
#include "Components.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "../Components/ItemComponent.h"
#include "../Components/ScoreComponent.h"
#include "../Components/BubbleComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/Enemies/ZenChanEnemyComponent.h"

using namespace OatmealEngine;

std::shared_ptr<OatmealEngine::GameObject> Prefabs::Player(const glm::vec3& position, PlayerIndex playerID, int animationStartRow)
{
	auto pScene{SceneManager::GetInstance().GetActiveScene().lock()};
	auto go{pScene->NewGameObject()};
	go->SetTag("Player");
	go->AddComponent(std::make_shared<SpriteComponent>(ResourceManager::GetInstance().LoadTexture("Characters"), SDL_Point{16, 16}, animationStartRow, 0));
	auto pPlayer{go->AddComponent(std::make_shared<PlayerComponent>(playerID))};

	auto pCollider = go->AddComponent(std::make_shared<ColliderComponent>(16, 16));
	go->AddComponent(std::make_shared<RigidbodyComponent>(pCollider));
	pCollider->SetOnCollideCallback(std::bind(&PlayerComponent::OnCollide, pPlayer, std::placeholders::_1));

	auto animation = go->AddComponent(std::make_shared<AnimationComponent>());
	animation->AddAnimation("Idle",
		{
			AnimationComponent::FrameDesc(animationStartRow,0,-1),
		}
	);
	animation->AddAnimation("Move",
		{
			AnimationComponent::FrameDesc(animationStartRow,0,.05f),
			AnimationComponent::FrameDesc(animationStartRow,1,.05f),
			AnimationComponent::FrameDesc(animationStartRow,2,.05f),
			AnimationComponent::FrameDesc(animationStartRow,3,.05f),
			AnimationComponent::FrameDesc(animationStartRow,4,.05f),
			AnimationComponent::FrameDesc(animationStartRow,5,.05f),
			AnimationComponent::FrameDesc(animationStartRow,6,.05f),
			AnimationComponent::FrameDesc(animationStartRow,7,.05f),
		}
	);
	animation->AddAnimation("Shoot",
		{
			AnimationComponent::FrameDesc(animationStartRow+1,0,.1f),
			AnimationComponent::FrameDesc(animationStartRow+1,4,.1f),
			AnimationComponent::FrameDesc(animationStartRow+1,0,.1f),
		}
	);
	animation->AddAnimation("Hit",
		{
			AnimationComponent::FrameDesc(animationStartRow+2,0,.25f),
			AnimationComponent::FrameDesc(animationStartRow+2,1,.25f),
			AnimationComponent::FrameDesc(animationStartRow+2,2,.25f),
			AnimationComponent::FrameDesc(animationStartRow+2,3,.25f),
		}
	);

	go->GetTransform().SetPosition(position);

	return go;
}

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

std::shared_ptr<OatmealEngine::GameObject> Prefabs::Item(const glm::vec3& position, const std::weak_ptr<Texture2D>& textureItem, const std::weak_ptr<Texture2D>& texturePoints, int points, int animationStartRow, int animationStartCol)
{
	auto pScene{SceneManager::GetInstance().GetActiveScene().lock()};
	auto go{pScene->NewGameObject()};
	go->SetTag("Item");

	go->AddComponent(std::make_shared<SpriteComponent>(textureItem, SDL_Point{16,16}, 1, 0));

	auto pCollider = go->AddComponent(std::make_shared<ColliderComponent>(16, 16));

	auto pRigidbody{go->AddComponent(std::make_shared<RigidbodyComponent>(pCollider))};

	auto pItem{go->AddComponent(std::make_shared<ItemComponent>(texturePoints, points, animationStartRow, animationStartCol))};
	pCollider->SetOnCollideCallback(std::bind(&ItemComponent::OnCollide, pItem, std::placeholders::_1));

	go->GetTransform().SetPosition(position);
	return go;
}

std::shared_ptr<OatmealEngine::GameObject> Prefabs::Points(const glm::vec3& position, const std::weak_ptr<OatmealEngine::Texture2D>& texturePoints, int animationStartRow, int animationStartCol)
{
	auto pScene{SceneManager::GetInstance().GetActiveScene().lock()};
	auto go{pScene->NewGameObject()};

	go->AddComponent(std::make_shared<SpriteComponent>(texturePoints, SDL_Point{16,16}, animationStartRow, animationStartCol));
	go->AddComponent(std::make_shared<ScoreComponent>());

	go->GetTransform().SetPosition(position);
	return go;
}
