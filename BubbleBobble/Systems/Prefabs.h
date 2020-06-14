#pragma once

#include "GameObject.h"

class Prefabs
{
public:
	static std::shared_ptr<OatmealEngine::GameObject> Bubble(const glm::vec3& position, int directionX, int animationStartCol);
	static std::shared_ptr<OatmealEngine::GameObject> ZenChan(const glm::vec3& position);
};

