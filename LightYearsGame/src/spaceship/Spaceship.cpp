#include "framework/MathUtility.h"
#include "spaceship/Spaceship.h"
#include "VFX/Explosion.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComp{ 100.f, 100.f },
		mBlinkTime{ 0.f },
		mBlinkDuration{ 0.2f },
		mBlinkColorOffset{ 255, 0, 0, 255 }
	{
	}
	void Spaceship::Tick(float deltatime)
	{
		Actor::Tick(deltatime);
		AddActorLocationOffset(GetVelocity() * deltatime);
		UpdateBlink(deltatime);
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

	void Spaceship::Blink()
	{
		if (mBlinkTime == 0.f)
		{
			mBlinkTime = mBlinkDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltatime)
	{
		if (mBlinkTime > 0)
		{
			mBlinkTime -= deltatime;
			mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

			GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}

	void Spaceship::OnHealthChange(float amt, float health, float maxHealth)
	{
		LOG("health changed by: %f, and is now: %f/%f", amt, health, maxHealth);
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::Blow()
	{
		Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());
		Destroy();
		delete exp;
	}


}
