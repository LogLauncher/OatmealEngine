#pragma once
#include "SceneManager.h"

namespace OatmealEngine
{
	class SceneManager;
	class GameObject;
	class RenderComponent;
	class RigidbodyComponent;

	class BaseScene : public std::enable_shared_from_this<BaseScene>
	{
	public:
		std::shared_ptr<GameObject> NewGameObject();
		bool Remove(const std::shared_ptr<GameObject>& object);

		virtual void OnSceneLoad() {};
		virtual void OnSceneUnload() {};

		explicit BaseScene(const std::string& name);
		~BaseScene() = default;
		DEL_ROF(BaseScene);

		const std::string& GetName() const { return m_Name; }

		void AddRenderComponent(const std::shared_ptr<RenderComponent>& pRenderComponent);
		void AddRigidbodyComponent(const std::weak_ptr<RigidbodyComponent>& pRigidbodyComponent);

	protected:
		virtual void Initialize() = 0;

	private:
		friend class SceneManager;

		void RootStart() const;
		void RootFixedUpdate() const;
		void RootUpdate() const;
		void RootLateUpdate() const;
		void RootRender() const;

		void UpdateCollision() const;

#ifdef _DEBUG
		void RootDebugRender() const;
#endif

		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_pObjects{};
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents{};
		std::vector<std::weak_ptr<RigidbodyComponent>> m_pRigidbodyComponents{};
		bool m_IsInitialized;

	};

}
