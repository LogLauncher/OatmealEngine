#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace OatmealEngine
{
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		DEL_ROF(GameObject);

		void RootAwake();
		void RootStart();
		void RootFixedUpdate();
		void RootUpdate();
		void RootLateUpdate();
		void RootRender() const;

		TransformComponent& GetTransform();
		void AddComponent(std::shared_ptr<BaseComponent> component);

	private:
		TransformComponent m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

	};
}
