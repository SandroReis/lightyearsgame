#pragma once

#include "weapon/BulletShooter.h"
#include <SFML/Graphics.hpp>

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = { 0.f,0.f });

		BulletShooter mShooterLeft;
		BulletShooter mShooterMid;
		BulletShooter mShooterRight;

		BulletShooter mTopLevelShooterLeft;
		BulletShooter mTopLevelShooterRight;

		virtual bool IsOnCooldown() override;
		std::string& GetBulletSound() { return mBulletSoundPath; };

		virtual void IncrementLevel(int amt) override;
		virtual void SetCurrentLevel(int level) override;

	private:
		std::string mBulletSoundPath;
		virtual void ShootImpl() override;
	};
}