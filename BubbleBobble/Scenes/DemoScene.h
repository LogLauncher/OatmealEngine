#pragma once
#include "BaseScene.h"

class DemoScene : public OatmealEngine::BaseScene
{
public:
	DemoScene();
	virtual ~DemoScene() = default;

	virtual void Initialize() override;

private:
	void LoadResources() const;

};

