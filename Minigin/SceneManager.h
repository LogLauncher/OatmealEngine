#pragma once
#include "Singleton.h"
#include <map>

namespace OatmealEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(std::shared_ptr<Scene> scene);
		bool LoadScene(const std::string& name);

		void Initialize();

		void RootFixedUpdate();
		void RootUpdate();
		void RootLateUpdate();
		void RootRender() const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::map<std::string, std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}
