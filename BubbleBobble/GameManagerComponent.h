#pragma once
#include "BaseComponent.h"

class GameManagerComponent : public OatmealEngine::BaseComponent
{
public:
	explicit GameManagerComponent();
	virtual ~GameManagerComponent() = default;
	DEL_ROF(GameManagerComponent);

	virtual void Awake() override;
	virtual void Update() override;

private:
	bool m_SecondPlayer;
};

