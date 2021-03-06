#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//SDL2
#include "SDL_rect.h"

// glm
#pragma warning(push)
#pragma warning (disable:4201)
#include "vec2.hpp"
#include "vec3.hpp"
#pragma warning(pop)

#include "GameSettings.h"
#include "Utils.h"

// Delete
#define DEL_ROF(classToDel) \
classToDel(const classToDel&) = delete; \
classToDel(classToDel&&) = delete; \
classToDel& operator=(const classToDel&) = delete; \
classToDel& operator=(classToDel&&) = delete; \

