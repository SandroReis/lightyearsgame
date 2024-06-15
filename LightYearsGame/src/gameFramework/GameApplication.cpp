#include "config.h"
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

		weak<Spaceship> testSpaceShip = newWorld.lock()->SpawnActor<Spaceship>();
		testSpaceShip.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip2_orange.png");
		testSpaceShip.lock()->SetActorLocation(sf::Vector2f{ 100.f, 50.f });
		testSpaceShip.lock()->SetTeamId(2);
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