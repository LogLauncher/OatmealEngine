#pragma once
#include <memory>

#include "BaseScene.h"
#include "Texture2D.h"

class LevelBuilder
{
public:
	static bool Build(int levelNr, const std::shared_ptr<OatmealEngine::BaseScene>& pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture, std::vector<std::weak_ptr<OatmealEngine::GameObject>>& pLevelBlocks);

private:
	static std::shared_ptr<OatmealEngine::GameObject> CreateFullBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, const std::shared_ptr<OatmealEngine::BaseScene>& pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture);
	static std::shared_ptr<OatmealEngine::GameObject> CreatePlatformBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, const std::shared_ptr<OatmealEngine::BaseScene>& pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture);

};

