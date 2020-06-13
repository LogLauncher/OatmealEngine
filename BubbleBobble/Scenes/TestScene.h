#pragma once
#include "BaseScene.h"

class TestScene : public OatmealEngine::BaseScene
{
public:
	TestScene();
	virtual ~TestScene() = default;

	virtual void Initialize() override;

private:
	void LoadResources() const;

};

