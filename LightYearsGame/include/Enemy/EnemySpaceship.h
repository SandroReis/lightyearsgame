#pragma once

#include "player/Reward.h"
#include "spaceship/Spaceship.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld,
			const std::string& texturePath,
			float collisionDamage = 200.f,
			const List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontWiperReward
			}
		);
		virtual void Tick(float deltaTime) override;
		void SetScoreAwardAmt(unsigned int amt);
	private:
		void SpawnReward();
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;
		unsigned int mScoreAwardAmt;

		List<RewardFactoryFunc> mRewardFactories;

	};
}