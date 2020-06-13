#pragma once
#include "TransformComponent.h"

namespace OatmealEngine
{
	class BaseScene;
	class BaseComponent;
	class RenderComponent;
	class RigidbodyComponent;

	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;
		DEL_ROF(GameObject);

		void RootAwake();
		void RootStart();
		void RootFixedUpdate();
		void RootUpdate();
		void RootLateUpdate();

#ifdef _DEBUG
		void RootDebugRender() const;
#endif

		void SetScene(const std::weak_ptr<BaseScene>& pBaseScene);
		std::weak_ptr<BaseScene> GetScene() const;

		TransformComponent& GetTransform();
// 		std::shared_ptr<BaseComponent> AddComponent(const std::shared_ptr<BaseComponent>& pComponent);
		template <class T>
		std::shared_ptr<T> AddComponent(const std::shared_ptr<T>& pComponent);
		std::shared_ptr<RenderComponent> AddComponent(const std::shared_ptr<RenderComponent>& pComponent);
		std::shared_ptr<RigidbodyComponent> AddComponent(const std::shared_ptr<RigidbodyComponent>& pComponent);
		
		template <class T>
		std::weak_ptr<T> GetComponent() const;

	private:
		TransformComponent m_Transform;
		std::weak_ptr<BaseScene> m_pBaseScene;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

	};

	template <class T>
	std::shared_ptr<T> OatmealEngine::GameObject::AddComponent(const std::shared_ptr<T>& pComponent)
	{
		m_pComponents.push_back(pComponent);
		pComponent->SetGameObject(shared_from_this());
		pComponent->Awake();

		return pComponent;
	}

	template <class T>
	std::weak_ptr<T> OatmealEngine::GameObject::GetComponent() const
	{
		const type_info& ti = typeid(T);
		for (auto pComponent : m_pComponents)
		{
			if (pComponent && typeid(*pComponent) == ti)
				return std::static_pointer_cast<T>(pComponent);
		}
		return {};
	}

// 	template <class T>
// 	std::shared_ptr<T> AddComponent(const std::shared_ptr<T>& pComponent)
// 	{
// 		m_pComponents.push_back(pComponent);
// 		pComponent->SetGameObject(shared_from_this());
// 		pComponent->Awake();
// 
// 		return pComponent;
// 	}

}
