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
	private:
		void CheckMove();
		float mSpeed;
		float mSwitchDistanceToEdge;

		BulletShooter mBaseShooterLeft;
		BulletShooter mBaseShooterRight;

		void ShotBaseShooters();

	};
}