#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComp{ 100.f, 100.f }
	{
	}
	void Spaceship::Tick(float deltatime)
	{
		Actor::Tick(deltatime);
		AddActorLocationOffset(GetVelocity() * deltatime);
	}
	void Spaceship::SetVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}

	void Spaceship::Shoot()
	{
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		weak<Object> selfRef = GetWeakRef();
		mHealthComp.onHealthChange.BindAction(selfRef, &Spaceship::OnHealthChange);
		mHealthComp.onTakenDamage.BindAction(selfRef, &Spaceship::OnTakenDamage);
		mHealthComp.onHealthEmpty.BindAction(selfRef, &Spaceship::Blow);

	}

	void Spaceship::ApplyDamage(float amt)
	{
		mHealthComp.ChangeHealth(-amt);
	}

	void Spaceship::OnHealthChange(float amt, float health, float maxHealth)
	{
		LOG("health changed by: %f, and is now: %f/%f", amt, health, maxHealth);
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
	}

	void Spaceship::Blow()
	{
		Destroy();
	}


}
