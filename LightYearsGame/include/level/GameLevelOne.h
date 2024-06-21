#pragma once
#include "framework/TimerManager.h"
#include "framework/World.h"

namespace ly
{
	class PlayerSpaceship;
	class GameplayHUD;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);

	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceship> mPlayerSpaceship;
		weak<GameplayHUD> mGameplayHUD;

		virtual void InitGameStage() override;
		void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceship);
		void GameOver();
	};
}