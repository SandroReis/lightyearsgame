#pragma once

#include "Enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/FrontWiper.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);
		virtual void Tick(float deltatime) override;
		virtual void BeginPlay() override;
	private:
		void CheckMove();
		float mSpeed;
		float mBaseSpeed;
		float mSwitchDistanceToEdge;

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;

		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontWayShooter();

		BulletShooter mFinalStageShooterLeft;
		BulletShooter mFinalStageShooterRight;


		ThreeWayShooter mThreeWayShooter;
		FrontWiper mFrontWiperLeft;
		FrontWiper mFrontWiperRight;

		int mStage;

		void HealthChanged(float amt, float currentHealth, float maxHealth);

		void SetStage(int newStage);
	};
}