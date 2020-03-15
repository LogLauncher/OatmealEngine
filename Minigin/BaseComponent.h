#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent();

		virtual void Update(float deltaTime) = 0;
		virtual void Render() const = 0;

		std::weak_ptr<GameObject> GetGameObject() const;
		void SetGameObject(std::weak_ptr<GameObject> pGameObject);

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	private:
		std::weak_ptr<GameObject> m_pGameObject;

	};

}
