#pragma once
#include "spaceship/Spaceship.h"


namespace ly
{
	class Shooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; };
		float GetSpeed() { return mSpeed; };
		void SetShooter(unique<Shooter>&& newShooter);

	public:
		virtual void Tick(float deltatime) override;
		virtual void Shoot() override;

	private:
		void NormalizeInput();
		void ClampInputOnEdge();
		void HandleInput();
		void ConsumeInput(float deltatime);

	private:
		float mSpeed;
		sf::Vector2f mMoveInput;
		unique<Shooter> mShooter;


	};
}