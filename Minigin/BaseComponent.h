#pragma once

namespace OatmealEngine
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent();
		DEL_RO4(BaseComponent);

		virtual void Awake();
		virtual void Start();

		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();

		virtual void Render() const;

		std::weak_ptr<GameObject> GetGameObject() const;
		void SetGameObject(std::weak_ptr<GameObject> pGameObject);


	private:
		std::weak_ptr<GameObject> m_pGameObject;

	};

}
