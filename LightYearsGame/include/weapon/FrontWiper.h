#pragma once
#include "weapon/BulletShooter.h"
#include <SFML/Graphics.hpp>

namespace ly
{
	class FrontWiper : public Shooter
	{

	public:
		FrontWiper(Actor* owner,
			float cooldownTime = 0.3f,
			const sf::Vector2f& localOffset = { 0.f,0.f },
			float width = 60.f
		);


	private:
		virtual void ShootImpl() override;


		float mWidth;

		BulletShooter mShooter1;
		BulletShooter mShooter2;
		BulletShooter mShooter3;
		BulletShooter mShooter4;


	};
}