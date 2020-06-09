#pragma once
#include "Singleton.h"

namespace OatmealEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<OatmealEngine::Scene> CreateScene(const std::string& name);

		void Awake();
		void Start();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
