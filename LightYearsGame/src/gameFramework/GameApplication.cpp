#include "config.h"
#include "Enemy/Vanguard.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
#include "gameFramework/GameApplication.h"
#include "player/PlayerSpaceship.h"

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
		weak<World> newWorld = LoadWorld<World>();
		testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceShip = newWorld.lock()->SpawnActor<Vanguard>();
		testSpaceShip.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
		//counter = 0.f;
	}
	void GameApplication::Tick(float deltatime)
	{
		//counter += deltatime;
		//if (counter > 10.f)
		//{
		//	if (!testPlayerSpaceship.expired())
		//	{
		//		testPlayerSpaceship.lock()->Destroy();
		//	}
		//}
	}
}