#include "framework/SoundSystem.h"
#include "weapon/Shooter.h"

namespace ly
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootImpl();
		}
	}
	void Shooter::IncrementLevel(int amt)
	{
		if (mCurrentLevel == mMaxLevel) return;
		++mCurrentLevel;
	}
	void Shooter::SetCurrentLevel(int level)
	{
		mCurrentLevel = level;
	}
	Shooter::Shooter(Actor* owner, const std::string& bulletSoundPath)
		: mOwner{ owner },
		mCurrentLevel{ 1 },
		mMaxLevel{ 4 },
		mBulletSoundPath{}
	{
		SetBulletSound(bulletSoundPath);
	}
}