#pragma once
#include "Singleton.h"
#include <map>

namespace OatmealEngine
{
	class BaseScene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(std::shared_ptr<BaseScene> scene);
		bool SetStartScene(const std::string& name);
		bool LoadScene(const std::string& name);

		void Initialize();

	private:
		friend class Minigin;
		friend class Renderer;
		friend class Singleton<SceneManager>;

		SceneManager() = default;
		std::map<std::string, std::shared_ptr<BaseScene>> m_Scenes;
		std::shared_ptr<BaseScene> m_ActiveScene;

		void RootFixedUpdate();
		void RootUpdate();
		void RootLateUpdate();
		void RootRender() const;

	};
}
