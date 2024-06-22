#pragma once
#include "widgets/HUD.h"
#include "widgets/ImageWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"


namespace ly {
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltatime) override;


	private:
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int amt);

		virtual void Init(const sf::RenderWindow& windowRef) override;
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		TextWidget mFramerateText;
		TextWidget mPlayerLifeCountText;
		ValueGuage mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;


		void RefreshHealthBar();
		void ObserverPlayerStats();

		void PlayerSpaceshipDestroyed(Actor* actor);
		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;
		float mCriticalThreshould;

		float mWidgetSpacing;

	};
}