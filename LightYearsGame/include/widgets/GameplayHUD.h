#pragma once
#include "widgets/Button.h"
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

		virtual bool HandleEvent(const sf::Event& event) override;
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


		//TODO: remove
		void TestButtonClick();
		//TODO: remove
		Button TestButton;


		void RefreshHealthBar();
		void ObserverPlayerStats();

		void PlayerSpaceshipDestroyed(Actor* actor);
		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;
		float mCriticalThreshould;

		float mWidgetSpacing;

	};
}