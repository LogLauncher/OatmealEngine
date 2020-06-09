#pragma once
#include "SceneManager.h"

namespace OatmealEngine
{
	class SceneManager;
	class GameObject;

	class BaseScene 
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

	protected:
		virtual void Initialize() = 0;

	private:
		friend class SceneManager;

		void RootAwake();
		void RootStart();
		void RootFixedUpdate();
		void RootUpdate();
		void RootLateUpdate();
		void RootRender() const;

		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_Objects{};
		bool m_IsInitialized;

	};

}
