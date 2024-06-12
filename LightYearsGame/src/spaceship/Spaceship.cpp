#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{owningWorld, texturePath},
		mVelocity{}
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
}
