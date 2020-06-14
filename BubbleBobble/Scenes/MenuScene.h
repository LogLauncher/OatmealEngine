#pragma once
#include "BaseScene.h"

class MenuScene : public OatmealEngine::BaseScene
{
public:
	explicit MenuScene();
	virtual ~MenuScene() = default;

protected:
	virtual void Initialize() override;
	virtual void Update() override;

};

