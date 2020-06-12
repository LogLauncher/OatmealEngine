#pragma once
#include "SceneManager.h"

namespace OatmealEngine
{
	class SceneManager;
	class GameObject;
	class RenderComponent;

	class BaseScene : public std::enable_shared_from_this<BaseScene>
	{
	public:
		std::shared_ptr<GameObject> GetNewGameObject();
		bool Remove(const std::shared_ptr<GameObject>& object);

		virtual void OnSceneLoad() {};
		virtual void OnSceneUnload() {};

		explicit BaseScene(const std::string& name);
		~BaseScene() = default;
		DEL_ROF(BaseScene);

		const std::string& GetName() const { return m_Name; }

		void AddRenderComponent(const std::shared_ptr<RenderComponent>& pRenderComponent);

	protected:
		virtual void Initialize() = 0;

	private:
		friend class SceneManager;

		void RootStart();
		void RootFixedUpdate();
		void RootUpdate();
		void RootLateUpdate();
		void RootRender() const;

#ifdef _DEBUG
		void RootDebugRender() const;
#endif

		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_pObjects{};
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents{};
		bool m_IsInitialized;

	};

}
