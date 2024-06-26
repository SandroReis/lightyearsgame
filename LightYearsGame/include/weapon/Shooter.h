#pragma once
#include "framework/Core.h"
#include <string>

namespace ly
{
	class Actor;
	class Shooter
	{
	public:
		virtual void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() { return false; }
		Actor* GetOwner() const { return mOwner; }

		int GetCurrentLevel() const { return mCurrentLevel; }
		int GetMaxLevel() const { return mMaxLevel; }

		virtual void IncrementLevel(int amt = 1);
		virtual void SetCurrentLevel(int level);
		std::string& GetBulletSound() { return mBulletSoundPath; };
		void SetBulletSound(const std::string& bulletSoundPath) { mBulletSoundPath = bulletSoundPath; };


	protected:
		Shooter(Actor* owner, const std::string& bulletSoundPath = "SpaceShooterRedux/sounds/sound_effects/Longshot.ogg");


	private:
		std::string mBulletSoundPath;
		virtual void ShootImpl() = 0;
		Actor* mOwner;


		int mCurrentLevel;
		int mMaxLevel;
	};
}