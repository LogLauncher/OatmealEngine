#pragma once
#include <memory>
#include "BaseScene.h"
#include "Texture2D.h"

class LevelBuilder
{
public:
	static bool Build(int levelNr, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture);

private:
	static void CreateFullBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture);
	static void CreatePlatformBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture);

};

