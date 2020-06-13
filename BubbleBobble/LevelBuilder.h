#pragma once
#include <memory>
#include "BaseScene.h"
#include "Texture2D.h"

class LevelBuilder
{
public:
	static void Build(int levelNr, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture);

private:
	static void CreateBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture);

};

