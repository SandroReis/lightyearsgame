#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "level/GameLevelOne.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{ owningApp }
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300, 490.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

	}
	void GameLevelOne::BeginPlay()
	{
	}
	void GameLevelOne::InitGameStage()
	{
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});
	}
}