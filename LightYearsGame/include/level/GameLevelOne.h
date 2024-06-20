#pragma once
#include "framework/TimerManager.h"
#include "framework/World.h"

namespace ly
{
	class PlayerSpaceship;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);

	private:
		virtual void BeginPlay() override;
		weak<PlayerSpaceship> mPlayerSpaceship;
		virtual void InitGameStage() override;
		void PlayerSpaceShipDestroyed(Actor* destroyedPlayerSpaceship);
		void GameOver();
	};
}