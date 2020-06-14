#pragma once
#include "Singleton.h"

#include "BaseScene.h"

class GameManager final : public OatmealEngine::Singleton<GameManager>
{
public:
	explicit GameManager();
	virtual ~GameManager() = default;
	DEL_ROF(GameManager);

	void Initialize();
	void Update();
	
	void LoadLevel(int levelID);

private:
	std::vector<std::weak_ptr<OatmealEngine::GameObject>> m_pLevelBlocks;
	
	int m_LevelID;
	
	bool m_SecondPlayer;
	bool m_IsInitialized;

	void AddSecondPlayer();

};

