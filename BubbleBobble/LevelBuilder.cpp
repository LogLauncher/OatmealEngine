#include "LevelBuilder.h"
#include "BinaryReader.h"

#include <iostream>

#include "Components.h"
#include "GameObject.h"

void LevelBuilder::Build(int levelNr, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture)
{
	const int nrLevelsTotal{100};
	const int levelWidth{32};
	const int levelHeight{25};
	const int blockPerByte{8};

	const int rowSpriteSheet{(levelNr - 1) / 10};
	const int colSpriteSheet{(levelNr - 1) % 10};

	OatmealEngine::BinaryReader reader{};
	reader.Open("Resources/SeperatedLevelData.dat");

	// Set reader to the correct level
	reader.SetBufferPosition((levelNr - 1) * nrLevelsTotal);

	// Read level & create blocks
	for (int height{}; height < levelHeight; ++height)
	{
		for (int width{}; width < levelWidth / blockPerByte; ++width)
		{
			int blocks{reader.Read<unsigned char>()};
			if (blocks & 0b10000000)
				CreateBlock(height, width * blockPerByte, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			if (blocks & 0b01000000)
				CreateBlock(height, width * blockPerByte + 1, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			if (blocks & 0b00100000)
				CreateBlock(height, width * blockPerByte + 2, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			if (blocks & 0b00010000)
				CreateBlock(height, width * blockPerByte + 3, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			if (blocks & 0b00001000)
				CreateBlock(height, width * blockPerByte + 4, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			if (blocks & 0b00000100)
				CreateBlock(height, width * blockPerByte + 5, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			if (blocks & 0b00000010)
				CreateBlock(height, width * blockPerByte + 6, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
			if (blocks & 0b00000001)
				CreateBlock(height, width * blockPerByte + 7, rowSpriteSheet, colSpriteSheet, pScene, pTexture);
		}
	}
}


void LevelBuilder::CreateBlock(int rowWorld, int colWorld, int rowSpriteSheet, int colSpriteSheet, OatmealEngine::BaseScene* pScene, const std::shared_ptr<OatmealEngine::Texture2D>& pTexture)
{
	const SDL_Point blockSize{8, 8};
	const float scale{3};

	auto go = pScene->NewGameObject();
	go->AddComponent(std::make_shared<OatmealEngine::SpriteComponent>(pTexture, blockSize, rowSpriteSheet, colSpriteSheet));
	auto collider{std::make_shared<OatmealEngine::ColliderComponent>(blockSize)};
	go->AddComponent(collider);
	go->AddComponent(std::make_shared<OatmealEngine::RigidbodyComponent>(collider, true));
	go->GetTransform().SetPosition(colWorld * blockSize.x * scale, rowWorld * blockSize.y * scale);
	go->GetTransform().SetScale(scale, scale);
}