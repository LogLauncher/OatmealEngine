#pragma once
#include "TransformComponent.h"

namespace OatmealEngine
{
	class BaseScene;
	class BaseComponent;
	class RenderComponent;

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
		void AddComponent(const std::shared_ptr<BaseComponent>& pComponent);
		void AddComponent(const std::shared_ptr<RenderComponent>& pComponent);

	private:
		TransformComponent m_Transform;
		std::weak_ptr<BaseScene> m_pBaseScene;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

	};
}
