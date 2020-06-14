#pragma once
#include "BaseScene.h"

class MainScene final : public OatmealEngine::BaseScene
{
public:
	explicit MainScene();
	virtual ~MainScene() = default;

protected:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void OnSceneLoad() override;

};

