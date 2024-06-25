#include "framework/Actor.h"
#include "framework/SoundSystem.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFramerateText{ "Frame rate:" },
		mPlayerHealthBar{},
		mPlayerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" },
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerLifeCountText{ "" },
		mPlayerScoreText{ "" },
		mHealthyHealthBarColor{ 128,255,128,255 },
		mCriticalHealthBarColor{ 255,0,0,255 },
		mCriticalThreshould{ 0.35 },
		mWidgetSpacing{ 10.f },
		mWinLoseText{ "" },
		mFinalScoreText{ "" },
		mRestartButton{ "Restart" },
		mQuitButton{ "Quit" },
		mWindowSize{}
	{
		mFramerateText.SetTextSize(25);
		mPlayerLifeCountText.SetTextSize(20);
		mPlayerScoreText.SetTextSize(20);
		mWinLoseText.SetTextSize(40);
		mFinalScoreText.SetTextSize(40);


		mWinLoseText.SetVisiblity(false);
		mFinalScoreText.SetVisiblity(false);
		mRestartButton.SetVisiblity(false);
		mQuitButton.SetVisiblity(false);


	}
	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mWindowSize = windowRef.getSize();
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeCountText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);
		mWinLoseText.NativeDraw(windowRef);
		mFinalScoreText.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}
	void GameplayHUD::Tick(float deltatime)
	{
		int frameRate = int(1 / deltatime);
		std::string framerateStr = "Frame rate: " + std::to_string(frameRate);
		mFramerateText.SetString(framerateStr);
	}
	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		if (mRestartButton.HandleEvent(event)) return true;
		if (mQuitButton.HandleEvent(event)) return true;
		return HUD::HandleEvent(event);
	}
	void GameplayHUD::RestartButtonClicked()
	{
		onRestartBtnClicked.Broadcast();
	}
	void GameplayHUD::QuitButtonClicked()
	{
		onQuitBtnClicked.Broadcast();
	}
	void GameplayHUD::PlayerLifeCountUpdated(int amt)
	{
		mPlayerLifeCountText.SetString(std::to_string(amt));
	}
	void GameplayHUD::PlayerScoreUpdated(int amt)
	{
		mPlayerScoreText.SetString(std::to_string(amt));
	}
	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{

		auto windowSize = windowRef.getSize();
		mWindowSize = windowSize;

		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{ 20.f, windowSize.y - 50.f });
		sf::Vector2f nextIconPos = mPlayerHealthBar.GetWidgetLocation();

		nextIconPos += sf::Vector2f{ mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeIcon.SetWidgetLocation(nextIconPos);

		nextIconPos += sf::Vector2f{ mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeCountText.SetWidgetLocation(nextIconPos);


		nextIconPos += sf::Vector2f{ mPlayerLifeCountText.GetBound().width + mWidgetSpacing * 4, -2.f };
		mPlayerScoreIcon.SetWidgetLocation(nextIconPos);

		nextIconPos += sf::Vector2f{ mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 2.f };
		mPlayerScoreText.SetWidgetLocation(nextIconPos);



		RefreshHealthBar();
		ObserverPlayerStats();


		mWinLoseText.SetWidgetLocation({ windowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f,100.f });


		mFinalScoreText.SetWidgetLocation({ windowSize.x / 2.f - mFinalScoreText.GetBound().width / 2.f,200.f });

		mRestartButton.SetWidgetLocation({ windowSize.x / 2.f - mRestartButton.GetBound().width / 2.f, windowSize.y / 2.f });
		mQuitButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 50.f });

		mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
	}
	void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth < mCriticalThreshould)
		{
			mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
		}
		else
		{
			mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
		}
	}
	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player && !player->GetCurrentSpaceship().expired())
		{
			mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestroy.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);
			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp();
			healthComp.onHealthChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
			mPlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}
	void GameplayHUD::ObserverPlayerStats()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			mPlayerLifeCountText.SetString(std::to_string(player->GetLifeCount()));
			player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

			int playerScore = player->GetScore();
			mPlayerScoreText.SetString(std::to_string(playerScore));
			player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
		}

	}
	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}
	void GameplayHUD::GameFinished(bool playerWon)
	{
		mWinLoseText.SetVisiblity(true);
		mFinalScoreText.SetVisiblity(true);
		mRestartButton.SetVisiblity(true);
		mQuitButton.SetVisiblity(true);


		int score = PlayerManager::Get().GetPlayer()->GetScore();
		mFinalScoreText.SetString("Score: " + std::to_string(score));
		if (playerWon)
		{
			mWinLoseText.SetString("You win!");
		}
		else
		{
			mWinLoseText.SetString("You Lose!");
		}

		mWinLoseText.SetWidgetLocation({ mWindowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f,100.f });

		mFinalScoreText.SetWidgetLocation({ mWindowSize.x / 2.f - mFinalScoreText.GetBound().width / 2.f,200.f });
	}
}