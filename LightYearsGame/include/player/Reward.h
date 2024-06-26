#pragma once

#include "framework/Actor.h"
#include <functional>
namespace ly
{
	class PlayerSpaceship;
	class Reward;
	using RewardFunc = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunc = std::function<weak<Reward>(World*)>;
	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunction, float speed = 200.f);
		virtual void BeginPlay() override;
		virtual void Tick(float deltatime) override;
	private:
		virtual void OnActorBeginOverlap(Actor* otherActor) override;
		float mSpeed;
		RewardFunc mRewardFunc;
	};

	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreeWayShooterReward(World* world);
	weak<Reward> CreateFrontWiperReward(World* world);
	weak<Reward> CreateLifeReward(World* world);


	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreeWayShooter(PlayerSpaceship* player);
	void RewardFrontWiper(PlayerSpaceship* player);
	void RewardLife(PlayerSpaceship* player);


}