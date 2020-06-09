#pragma once
#include "Scene.h"

class DemoScene : public OatmealEngine::Scene
{
public:
	DemoScene();
	virtual ~DemoScene() = default;

	virtual void Initialize() override;

};

