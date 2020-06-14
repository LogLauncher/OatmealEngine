#pragma once

#include "Texture2D.h"
#include "GameObject.h"
#include "InputManager.h"

class Prefabs
{
public:
	static std::shared_ptr<OatmealEngine::GameObject> Player(const glm::vec3& position, OatmealEngine::PlayerIndex playerID, int animationStartRow);
	static std::shared_ptr<OatmealEngine::GameObject> Bubble(const glm::vec3& position, int directionX, int animationStartCol);
	static std::shared_ptr<OatmealEngine::GameObject> ZenChan(const glm::vec3& position);

	static std::shared_ptr<OatmealEngine::GameObject> Item(const glm::vec3& position, const std::weak_ptr<OatmealEngine::Texture2D>& textureItem, const std::weak_ptr<OatmealEngine::Texture2D>& texturePoints, int points, int animationStartRow, int animationStartCol);
	static std::shared_ptr<OatmealEngine::GameObject> Points(const glm::vec3& position, const std::weak_ptr<OatmealEngine::Texture2D>& texturePoints, int animationStartRow, int animationStartCol);

};

