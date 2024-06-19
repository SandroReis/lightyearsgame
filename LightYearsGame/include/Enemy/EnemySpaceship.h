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
	private:
		void SpawnReward();
		float mCollisionDamage;
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void Blew() override;

		List<RewardFactoryFunc> mRewardFactories;

	};
}