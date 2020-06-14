#pragma once
#include "BaseScene.h"

class MainScene final : public OatmealEngine::BaseScene
{
public:
	MainScene();
	virtual ~MainScene() = default;

protected:
	virtual void Initialize() override;
	virtual void Update() override;

private:
	void LoadResources() const;

};

