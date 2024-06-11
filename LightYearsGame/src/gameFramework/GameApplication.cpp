#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication()
		: Application{600,980, "LightYears", sf::Style::Titlebar | sf::Style::Close}
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		actorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		counter = 0;

	}
	void GameApplication::Tick(float deltatime)
	{
		counter += deltatime;
		if (counter > 2.f)
		{
			if (!actorToDestroy.expired()) {
				actorToDestroy.lock()->Destroy();
			}
		}
	}
}