#pragma once
#include "Singleton.h"

#include "BaseScene.h"

class GameManager final : public OatmealEngine::Singleton<GameManager>
{
public:
	enum class State
	{
		MENU,
		GAME,
	};

	explicit GameManager();
	virtual ~GameManager() = default;
	DEL_ROF(GameManager);

	void Initialize();
	void Update();
	
	void SetState(State state) { m_State = state; }

	void LoadLevel();

	void RemoveEnemy(std::weak_ptr<OatmealEngine::GameObject> pObject);

private:
	std::vector<std::weak_ptr<OatmealEngine::GameObject>> m_pLevelBlocks;
	std::vector<std::weak_ptr<OatmealEngine::GameObject>> m_pEnemies;
	
	int m_LevelID;

	const float m_TimeBeforeLevelSwitch;
	float m_TimerSwitchLevel;
	
	bool m_SecondPlayer;
	bool m_IsInitialized;

	State m_State;

	void AddSecondPlayer();

};

