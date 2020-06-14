#include "LevelBuilder.h"
#include "BinaryReader.h"

#include <iostream>

#include "Components.h"
#include "GameObject.h"

bool LevelBuilder::Build(int levelNr, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture)
{
	const int nrLevelsTotal{100};
	const int levelWidth{32};
	const int levelHeight{25};
	const int blockPerByte{8};

	const int outerWallWidth{2};
	const int outerWallHeight{1};

	const int rowSpriteSheet{(levelNr - 1) / 10};
	const int colSpriteSheet{(levelNr - 1) % 10};

	if (levelNr > nrLevelsTotal)
		return false;

	OatmealEngine::BinaryReader reader{};
	reader.Open("Resources/SeperatedLevelData.dat");

	// Set reader to the correct level
	reader.SetBufferPosition((levelNr - 1) * levelWidth * levelHeight / blockPerByte);

	// Read level & create blocks
	for (int height{}; height < levelHeight; ++height)
	{
		for (int width{}; width < levelWidth / blockPerByte; ++width)
		{
			int blocks{reader.Read<unsigned char>()};

			const int correctWidth{width * blockPerByte};

			// #TODO can faze through blocks while jumping (blocks with 1 above)

			if (blocks & 0b10000000)
			{
				if ((correctWidth < outerWallWidth || correctWidth >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
			if (blocks & 0b01000000)
			{
				if ((correctWidth + 1 < outerWallWidth || correctWidth + 1 >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth + 1, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth + 1, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
			if (blocks & 0b00100000)
			{
				if ((correctWidth + 2 < outerWallWidth || correctWidth + 2 >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth + 2, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth + 2, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
			if (blocks & 0b00010000)
			{
				if ((correctWidth + 3 < outerWallWidth || correctWidth + 3 >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth + 3, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth + 3, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
			if (blocks & 0b00001000)
			{
				if ((correctWidth + 4 < outerWallWidth || correctWidth + 4 >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth + 4, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth + 4, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
			if (blocks & 0b00000100)
			{
				if ((correctWidth + 5 < outerWallWidth || correctWidth + 5 >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth + 5, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth + 5, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
			if (blocks & 0b00000010)
			{
				if ((correctWidth + 6 < outerWallWidth || correctWidth + 6 >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth + 6, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth + 6, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
			if (blocks & 0b00000001)
			{
				if ((correctWidth + 7 < outerWallWidth || correctWidth + 7 >= levelWidth - outerWallWidth)
					|| (height < outerWallHeight || height >= levelHeight - outerWallHeight))
					CreateFullBlock(height, correctWidth + 7, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
				else
					CreatePlatformBlock(height, correctWidth + 7, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			}
		}
	}
	return true;
}


void LevelBuilder::CreateFullBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture)
{
	const SDL_Point blockSize{8, 8};
	const float scale{3};

	auto go = pScene->NewGameObject();
	go->AddComponent(std::make_shared<OatmealEngine::SpriteComponent>(pTexture, blockSize, rowSpriteSheet, colSpriteSheet));

	auto collider = go->AddComponent(std::make_shared<OatmealEngine::ColliderComponent>(blockSize));
	go->AddComponent(std::make_shared<OatmealEngine::RigidbodyComponent>(collider, true));

	go->GetTransform().SetPosition(colWorld * blockSize.x * scale, rowWorld * blockSize.y * scale);
	go->GetTransform().SetScale(scale, scale);
}

void LevelBuilder::CreatePlatformBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture)
{
	const SDL_Point blockSize{8, 8};
	const float scale{3};

	auto go = pScene->NewGameObject();
	go->AddComponent(std::make_shared<OatmealEngine::SpriteComponent>(pTexture, blockSize, rowSpriteSheet, colSpriteSheet));

	auto collider = go->AddComponent(std::make_shared<OatmealEngine::PlatformColliderComponent>(blockSize));
	go->AddComponent(std::make_shared<OatmealEngine::RigidbodyComponent>(collider, true));

	go->GetTransform().SetPosition(colWorld * blockSize.x * scale, rowWorld * blockSize.y * scale);
	go->GetTransform().SetScale(scale, scale);
}
