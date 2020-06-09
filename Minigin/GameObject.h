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
		DEL_RO4(GameObject);

		void Awake();
		void Start();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		TransformComponent& GetTransform();
		void AddComponenet(std::shared_ptr<BaseComponent> component);

	private:
		TransformComponent m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

	};
}
