#pragma once
#include "BaseScene.h"

class MainScene : public OatmealEngine::BaseScene
{
public:
	MainScene();
	virtual ~MainScene() = default;

	virtual void Initialize() override;

private:
	void LoadResources() const;

};

