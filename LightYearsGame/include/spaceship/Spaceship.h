#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "");
		sf::Vector2f GetVelocity() const { return mVelocity; };
		void SetVelocity(const sf::Vector2f& newVel);
		HealthComponent& GetHealthComp() { return mHealthComp; };
	public:
		virtual void Tick(float deltatime) override;
		virtual void Shoot();
		virtual void BeginPlay() override;
		virtual void ApplyDamage(float amt) override;


	private:
		void Blink();
		void UpdateBlink(float deltatime);
		virtual void OnHealthChange(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		void Blow();
		virtual void Blew();


	private:
		sf::Vector2f mVelocity;
		sf::Color mBlinkColorOffset;
		float mBlinkTime;
		float mBlinkDuration;
		HealthComponent mHealthComp;

	};
}