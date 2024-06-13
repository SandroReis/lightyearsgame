#pragma once
#include "spaceship/Spaceship.h"


namespace ly
{
	class BulletShooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltatime) override;
		void SetSpeed(float newSpeed) { mSpeed = newSpeed; };
		virtual void Shoot() override;
		float GetSpeed() { return mSpeed; };
	private:
		void NormalizeInput();
		void ClampInputOnEdge();
		void HandleInput();
		void ConsumeInput(float deltatime);
		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<BulletShooter> mShooter;
	};
}