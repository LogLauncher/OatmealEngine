#pragma once
#include "SceneManager.h"

namespace OatmealEngine
{
	class GameObject;
	class Scene final
	{
		friend std::shared_ptr<OatmealEngine::Scene> SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Awake();
		void Start();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		explicit Scene(const std::string& name);
		~Scene() = default;
		DEL_RO4(Scene);


	private:
		std::string m_Name;
		std::vector<std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};

}
