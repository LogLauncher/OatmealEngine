#pragma once
#include "Singleton.h"
#include <map>

namespace OatmealEngine
{
	class BaseScene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(const std::shared_ptr<BaseScene>& scene);
		bool SetStartScene(const std::string& name);
		bool LoadScene(const std::string& name);

		std::weak_ptr<BaseScene> GetActiveScene() const { return m_pActiveScene; }

		void Initialize();

	private:
		friend class Minigin;
		friend class Renderer;
		friend class Singleton<SceneManager>;

		SceneManager() = default;
		~SceneManager() = default;
		std::map<std::string, std::shared_ptr<BaseScene>> m_pScenes;
		std::weak_ptr<BaseScene> m_pActiveScene;

		void RootFixedUpdate() const;
		void RootUpdate() const;
		void RootLateUpdate() const;
		void RootRender() const;
		void RootUpdateCollision() const;
#ifdef _DEBUG
		void RootDebugRender() const;
#endif

	};
}
