#pragma once
#include "TransformComponent.h"

namespace OatmealEngine
{
	class GameObject;
	class BaseCollider;

	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		DEL_ROF(BaseComponent);

		virtual void Awake() {};
		virtual void Start() {};

		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

		virtual void OnTrigger(std::shared_ptr<BaseCollider> pOther) {};
		virtual void OnCollide(std::shared_ptr<BaseCollider> pOther) {};

#ifdef _DEBUG
		virtual void DebugRender() {};
#endif // _DEBUG

		void SetGameObject(std::weak_ptr<GameObject> pGameObject);
		std::weak_ptr<GameObject> GetGameObject() const;

		TransformComponent& GetTransform() const;

	private:
		std::weak_ptr<GameObject> m_pGameObject;

	};

}
