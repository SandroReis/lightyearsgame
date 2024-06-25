#pragma once
#include "widgets/Button.h"
#include "widgets/HUD.h"
#include "widgets/MainMenuHUD.h"
#include "widgets/TextWidget.h"


namespace ly
{

	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD();


		virtual bool HandleEvent(const sf::Event& event) override;
		virtual void Draw(sf::RenderWindow& windowRef) override;
		Delegate<> onStartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		TextWidget mTitleText;
		TextWidget mVolumeTipText;


		Button mStartButton;
		Button mQuitButton;

		void StartButtonClicked();
		void QuitButtonClicked();

	};
}