#pragma once
#include "Singleton.h"

namespace OatmealEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<OatmealEngine::Scene> CreateScene(const std::string& name);

		void Update(float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
