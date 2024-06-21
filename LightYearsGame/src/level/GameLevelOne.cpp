#include "Enemy/HexagonStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "level/GameLevelOne.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World{ owningApp }
	{



	}
	void GameLevelOne::BeginPlay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();

	}
	void GameLevelOne::InitGameStage()
	{


		//AddStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 4.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 4.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});
		AddStage(shared<WaitStage>{new WaitStage{ this, 4.f }});
		AddStage(shared<UFOStage>{new UFOStage{ this }});



	}
	void GameLevelOne::PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
		if (!mPlayerSpaceship.expired())
		{
			mPlayerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceShipDestroyed);
		}
		else
		{
			GameOver();
		}
	}
	void GameLevelOne::GameOver()
	{
	}
}