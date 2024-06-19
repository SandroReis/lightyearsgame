#pragma once

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include <SFML/Graphics.hpp>

namespace ly
{
	class UFOStage : public GameStage
	{
	public:
		UFOStage(World* world);

		virtual void StartStage() override;

	private:
		void SpawnUFO();
		virtual void StageFinished() override;
		sf::Vector2f GetRandomSpawnLoc() const;

		int mSpawnAmt;
		float mSpawnInterval;
		int mCurrentSpawnAmt;
		float mUFOSpeed;

		TimerHandle mSpawnTimer;
	};
}