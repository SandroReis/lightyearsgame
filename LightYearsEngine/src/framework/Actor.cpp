#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
	Actor::Actor(World* owningWorld)
		: mOwningWorld{ owningWorld },
		mHasBeganlay{false}
	{

	}
	Actor::~Actor()
	{
		LOG("Actor destroyed");
	}
	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganlay)
		{
			mHasBeganlay = true;
			BeginPlay();
		}
	}
	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}
	void Actor::Tick(float deltaTime)
	{
		LOG("Actor begin tick");

	}
}

