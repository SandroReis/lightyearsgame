#pragma once
#include "framework/TimerManager.h"
#include "spaceship/Spaceship.h"

namespace ly
{
	class Shooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; };
		float GetSpeed() { return mSpeed; };
		void SetShooter(unique<Shooter>&& newShooter);

	public:
		virtual void Tick(float deltatime) override;
		virtual void Shoot() override;
		virtual void ApplyDamage(float amt) override;
		virtual void BeginPlay() override;

	private:
		void UpdateInvulnerable(float deltatime);
		void StopInvunerable();
		void NormalizeInput();
		void ClampInputOnEdge();
		void HandleInput();
		void ConsumeInput(float deltatime);

	private:
		float mSpeed;
		float mInvulnerableTime;
		TimerHandle mInvulnerableTimerHandle;
		bool mIsInvulnerable;
		float mInvulnerableFlashInterval;
		float mInvulnerableFlashTimer;
		float mInvulnerableFlashDir;

		sf::Vector2f mMoveInput;
		unique<Shooter> mShooter;


	};
}