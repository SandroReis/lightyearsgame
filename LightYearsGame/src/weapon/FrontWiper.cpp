#include "weapon/FrontWiper.h"

namespace ly
{
	FrontWiper::FrontWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width)
		: Shooter{ owner },
		mWidth{ width },
		mShooter1{ owner, cooldownTime, {localOffset.x, localOffset.y - mWidth / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter2{ owner, cooldownTime, {localOffset.x, localOffset.y - mWidth / 6.f}, 0.f ,"SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter3{ owner, cooldownTime, {localOffset.x, localOffset.y + mWidth / 6.f}, 0.f,"SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter4{ owner, cooldownTime, {localOffset.x, localOffset.y + mWidth / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter5{ owner, 0.1, {localOffset.x, localOffset.y + mWidth / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter6{ owner, 0.1, {localOffset.x, localOffset.y - mWidth / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
	{
	}
	void FrontWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooter1.IncrementLevel(amt);
		mShooter2.IncrementLevel(amt);
		mShooter3.IncrementLevel(amt);
		mShooter4.IncrementLevel(amt);
	}
	void FrontWiper::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);
		mShooter1.SetCurrentLevel(level);
		mShooter2.SetCurrentLevel(level);
		mShooter3.SetCurrentLevel(level);
		mShooter4.SetCurrentLevel(level);
	}
	void FrontWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			mShooter5.Shoot();
			mShooter6.Shoot();
		}
	}
}