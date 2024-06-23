#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);
		virtual void Tick(float deltatime) override;
	private:
		float mSpeed;
		float mSwitchDistanceToEdge;
	};
}