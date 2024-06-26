#include "framework/World.h"
#include "player/PlayerManager.h"
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
		if (!otherActor || otherActor->IsPendingDestroy()) return;

		if (!PlayerManager::Get().GetPlayer()) return;

		weak<PlayerSpaceship> playerSpaceship = PlayerManager::Get().GetPlayer()->GetCurrentSpaceship();
		if (playerSpaceship.expired() || playerSpaceship.lock()->IsPendingDestroy()) return;

		if (playerSpaceship.lock()->GetUniqueID() == otherActor->GetUniqueID())
		{
			mRewardFunc(playerSpaceship.lock().get());
			Destroy();
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
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontWiper);
	}

	weak<Reward> CreateLifeReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png", RewardLife);
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
	void RewardLife(PlayerSpaceship* player)
	{
		if (!PlayerManager::Get().GetPlayer()) return;

		PlayerManager::Get().GetPlayer()->AddLifeCount(1);

	}
}