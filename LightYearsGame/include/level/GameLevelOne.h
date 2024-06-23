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
		virtual void AllGameStageFinished() override;

		virtual void BeginPlay() override;
		weak<PlayerSpaceship> mPlayerSpaceship;
		weak<GameplayHUD> mGameplayHUD;

		void SpawnCosmetics();

		virtual void InitGameStages() override;
		void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceship);
		void QuitGame();
		void RestartGame();
		void GameOver();
	};
}