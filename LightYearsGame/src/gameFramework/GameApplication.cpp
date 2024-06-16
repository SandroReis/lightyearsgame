#include "config.h"
#include "framework/AssetManager.h"
#include "gameFramework/GameApplication.h"
#include "level/GameLevelOne.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		: Application{ 600,980, "LightYears", sf::Style::Titlebar | sf::Style::Close }
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();

	}
}