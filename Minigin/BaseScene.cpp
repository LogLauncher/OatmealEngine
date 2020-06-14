#include "MiniginPCH.h"
#include "BaseScene.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "RigidbodyComponent.h"

OatmealEngine::BaseScene::BaseScene(const std::string& name)
	: m_Name(name)
	, m_IsInitialized{false}
{}

void OatmealEngine::BaseScene::AddRenderComponent(const std::shared_ptr<RenderComponent>& pRenderComponent)
{
	m_pRenderComponents.push_back(pRenderComponent);
}

void OatmealEngine::BaseScene::AddRigidbodyComponent(const std::weak_ptr<RigidbodyComponent>& pRigidbodyComponent)
{
	m_pRigidbodyComponents.push_back(pRigidbodyComponent);
}

std::shared_ptr<OatmealEngine::GameObject> OatmealEngine::BaseScene::NewGameObject()
{
	auto gameObject{std::make_shared<GameObject>()};
	gameObject->SetScene(shared_from_this());
	m_pObjectsToAdd.push_back(gameObject);
	return gameObject;
}

bool OatmealEngine::BaseScene::Remove(const std::shared_ptr<GameObject>& object)
{
	auto it = find(m_pObjectsToDelete.begin(), m_pObjectsToDelete.end(), object);
	if (it != m_pObjectsToDelete.end())
		return false;

	m_pObjectsToDelete.push_back(object);

	return true;
}

void OatmealEngine::BaseScene::RootStart()
{
	AddInternal();

	for (auto& object : m_pObjects)
		object->RootStart();
}

void OatmealEngine::BaseScene::RootFixedUpdate()
{
	for (auto& object : m_pObjects)
		object->RootFixedUpdate();

	AddInternal();
	RemoveInternal();
}

void OatmealEngine::BaseScene::RootUpdate()
{
	Update();

	for(auto& object : m_pObjects)
		object->RootUpdate();

	AddInternal();
	RemoveInternal();
}

void OatmealEngine::BaseScene::RootLateUpdate()
{
	for (auto& object : m_pObjects)
		object->RootLateUpdate();

	AddInternal();
	RemoveInternal();
}

void OatmealEngine::BaseScene::RootRender() const
{
	for (const auto& component : m_pRenderComponents)
		component->Render();
}

void OatmealEngine::BaseScene::UpdateCollision() const
{
	for (auto& pComponent : m_pRigidbodyComponents)
	{
		auto pRigidbody{pComponent.lock()};
		if (!pRigidbody->IsStatic())
			pRigidbody->UpdateCollision(m_pRigidbodyComponents);
	}
}

#ifdef _DEBUG
void OatmealEngine::BaseScene::RootDebugRender() const
{
	for (auto& object : m_pObjects)
		object->RootDebugRender();
}
#endif

void OatmealEngine::BaseScene::AddInternal()
{
	if (!m_pObjectsToAdd.empty())
	{
		for (auto& pObject : m_pObjectsToAdd)
		{
			m_pObjects.push_back(pObject);
			pObject->RootStart();
		}
		m_pObjectsToAdd.clear();
	}
}

void OatmealEngine::BaseScene::RemoveInternal()
{
	for (auto& pObject : m_pObjectsToDelete)
	{
		{
			auto it = find(m_pObjects.begin(), m_pObjects.end(), pObject);
			if (it == m_pObjects.end())
				continue;

			m_pObjects.erase(it);
		}

		auto pRender{pObject->GetComponent<RenderComponent>().lock()};
		if (pRender)
		{
			auto it = find(m_pRenderComponents.begin(), m_pRenderComponents.end(), pRender);
			if (it != m_pRenderComponents.end())
				m_pRenderComponents.erase(it);
		}

		auto pRigid{pObject->GetComponent<RigidbodyComponent>().lock()};
		if (pRigid)
		{
			auto it = find_if(m_pRigidbodyComponents.begin(), m_pRigidbodyComponents.end(), [pRigid](std::weak_ptr<RigidbodyComponent> pOtherRigid) {return pOtherRigid.lock() == pRigid; });
			if (it != m_pRigidbodyComponents.end())
				m_pRigidbodyComponents.erase(it);
		}

	}
	m_pObjectsToDelete.clear();
}

