#include "framework/Core.h"
#include "framework/SoundSystem.h"
#include "framework/World.h"
#include "weapon/Bullet.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime, sf::Vector2f localPositionOffset, float localRotationOffset, const std::string& bulletTexturePath)
		: Shooter{ owner },
		mCooldownClock{},
		mCooldownTime{ cooldownTime },
		mLocalPositionOffset{ localPositionOffset },
		mLocalRotationOffset{ localRotationOffset },
		mBulletTexturePath{ bulletTexturePath }
	{
	}
	bool BulletShooter::IsOnCooldown()
	{
		if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime / GetCurrentLevel())
		{
			return false;
		}

		return true;
	}
	void BulletShooter::SetBulletTexturePath(const std::string& bulletTexturePath)
	{
		mBulletTexturePath = bulletTexturePath;
	}

	void BulletShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
	}
	void BulletShooter::ShootImpl()
	{
		sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

		mCooldownClock.restart();

		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), mBulletTexturePath);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPositionOffset.x + ownerRightDir * mLocalPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);

	}
}