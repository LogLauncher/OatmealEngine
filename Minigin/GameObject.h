#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace OatmealEngine
{
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		TransformComponent& GetTransform();
		void AddComponenet(std::shared_ptr<BaseComponent> component);

		GameObject() = default;
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		TransformComponent m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

	};
}
