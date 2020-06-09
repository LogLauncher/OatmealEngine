#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Delete
#define DEL_RO4(classToDel) \
	classToDel(const classToDel&) = delete; \
	classToDel(classToDel&&) = delete; \
	classToDel& operator=(const classToDel&) = delete; \
	classToDel& operator=(classToDel&&) = delete; \

