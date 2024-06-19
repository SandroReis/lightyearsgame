#include "framework/World.h"
#include "player/PlayerSpaceship.h"
#include "player/Reward.h"
#include "weapon/FrontWiper.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunction, float speed)
		: Actor{ world, texturePath },
		mRewardFunc{ rewardFunction },
		mSpeed{ speed }
	{
	}
	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
	void Reward::Tick(float deltatime)
	{
		Actor::Tick(deltatime);
		AddActorLocationOffset({ 0.f, mSpeed * deltatime });
	}
	void Reward::OnActorBeginOverlap(Actor* otherActor)
	{
		//TODO: clean up casting
		PlayerSpaceship* playerSpaceship = static_cast<PlayerSpaceship*>(otherActor);
		if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
		{
			mRewardFunc(playerSpaceship);
		}
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_red.png", RewardHealth);
	}

	weak<Reward> CreateThreeWayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShooter);

	}

	weak<Reward> CreateFrontWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardThreeWayShooter);
	}

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmt = 10.f;
		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComp().ChangeHealth(rewardAmt);
		}
	}
	void RewardThreeWayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new ThreeWayShooter{ player, 0.4f, {50.f,0.f} }});
		}
	}
	void RewardFrontWiper(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{new FrontWiper{ player, 0.4f, {50.f,0.f} }});
		}

	}
}