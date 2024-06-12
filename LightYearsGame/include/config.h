#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else 
	return "D:/gamedev/projects/LightYears/LightYearsGame/assets/";
#endif
}
