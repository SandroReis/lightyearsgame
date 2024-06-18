#include "Enemy/Hexagon.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	Hexagon::Hexagon(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship{ owningWorld, texturePath },
		mShooter1{ new BulletShooter{this, 1.f, sf::Vector2f{20.f,50.f}, 30.f} }, //front right
		mShooter2{ new BulletShooter{this, 1.f, sf::Vector2f{20.f,-50.f}, -30.f} }, //front left
		mShooter3{ new BulletShooter{this, 1.f, sf::Vector2f{50.f,0.0f}} }, // front
		mShooter4{ new BulletShooter{this, 1.f, sf::Vector2f{-50.f,0.0f}, -180.f} }, // back
		mShooter5{ new BulletShooter{this, 1.f, sf::Vector2f{-20.f,50.f}, 120.f} },
		mShooter6{ new BulletShooter{this, 1.f, sf::Vector2f{-20.f,-50.f}, -120.f} }
	{

		SetVelocity(velocity);
		SetActorRotation(90.f);
	}
	void Hexagon::Tick(float deltatime)
	{

		EnemySpaceship::Tick(deltatime);
		Shoot();
	}
	void Hexagon::Shoot()
	{
		mShooter1->Shoot();
		mShooter2->Shoot();
		mShooter3->Shoot();
		mShooter4->Shoot();
		mShooter5->Shoot();
		mShooter6->Shoot();
	}
}