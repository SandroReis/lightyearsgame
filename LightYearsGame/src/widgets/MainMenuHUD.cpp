#include "framework/Core.h"
#include "framework/SoundSystem.h"
#include "SFML/System.hpp"
#include "widgets/MainMenuHUD.h"


namespace ly

{
	MainMenuHUD::MainMenuHUD()
		: mTitleText{ "Light Years" },
		mStartButton{ "Start" },
		mQuitButton{ "Quit" },
		mVolumeTipText{ "Pressione \"+\" ou \"-\" para ajustar o Volume" }
	{
		mTitleText.SetTextSize(40);
		mStartButton.SetTextSize(20);
		mQuitButton.SetTextSize(20);
		mVolumeTipText.SetTextSize(15);
	}
	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{

		bool start = mStartButton.HandleEvent(event);
		bool quit = mQuitButton.HandleEvent(event);
		return start || quit || HUD::HandleEvent(event);
	}
	void MainMenuHUD::Draw(sf::RenderWindow& windowRef)
	{
		mTitleText.NativeDraw(windowRef);
		mStartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
		mVolumeTipText.NativeDraw(windowRef);

	}
	void MainMenuHUD::Init(const sf::RenderWindow& windowRef)
	{
		sf::Vector2u windowSize = windowRef.getSize();
		mTitleText.SetWidgetLocation({ windowSize.x / 2.f - mTitleText.GetBound().width / 2.f,100.f });
		mVolumeTipText.SetWidgetLocation({ windowSize.x / 2.f - mVolumeTipText.GetBound().width / 2.f,300.f });

		mStartButton.SetWidgetLocation({ windowSize.x / 2.f - mStartButton.GetBound().width / 2.f, windowSize.y / 2.f });
		mQuitButton.SetWidgetLocation(mStartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 50.f });
		mStartButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);

		SoundSystem::Get().PlayMusic("SpaceShooterRedux/sounds/music/CrashedShip.ogg");

	}
	void MainMenuHUD::StartButtonClicked()
	{
		onStartButtonClicked.Broadcast();
	}
	void MainMenuHUD::QuitButtonClicked()
	{
		onQuitButtonClicked.Broadcast();
	}
}