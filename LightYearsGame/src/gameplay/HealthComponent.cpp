#include "framework/Core.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: mHealth{ health },
		mMaxHealth{ maxHealth }
	{
	}
	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0) return;

		if (mHealth == 0) return;

		mHealth += amt;
		if (mHealth < 0)
		{
			mHealth = 0;
		}

		if (mHealth > mMaxHealth)
		{
			mHealth = mMaxHealth;
		}

		if (amt < 0)
		{
			TakenDamage(-amt);
			if (mHealth <= 0)
			{
				HealthEmpty();
			}

		}
		/*else
		{
			HealthRegen(amt);
		}*/

		onHealthChange.Broadcast(amt, mHealth, mMaxHealth);

	}
	/*void HealthComponent::HealthRegen(float amt)
	{
		LOG("Health regen: %f, now health is: %f/%f", amt, mHealth, mMaxHealth);

	}*/
	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();

	}
	void HealthComponent::TakenDamage(float amt)
	{
		onTakenDamage.Broadcast(amt, mHealth, mMaxHealth);
	}
}