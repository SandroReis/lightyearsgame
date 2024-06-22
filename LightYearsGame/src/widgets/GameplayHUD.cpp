#include "framework/Actor.h"
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
		TestButton{}
	{
		mFramerateText.SetTextSize(25);
		mPlayerLifeCountText.SetTextSize(20);
		mPlayerScoreText.SetTextSize(20);

	}
	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeCountText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);
		TestButton.NativeDraw(windowRef);
	}
	void GameplayHUD::Tick(float deltatime)
	{
		int frameRate = int(1 / deltatime);
		std::string framerateStr = "Frame rate: " + std::to_string(frameRate);
		mFramerateText.SetString(framerateStr);
	}
	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		return TestButton.HandleEvent(event) || HUD::HandleEvent(event);
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

		TestButton.SetWidgetLocation({ windowSize.x / 2.f, windowSize.y / 2.f });
		TestButton.SetTextSize(20);
		TestButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::TestButtonClick);


		RefreshHealthBar();
		ObserverPlayerStats();
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
	void GameplayHUD::TestButtonClick()
	{
		LOG("Button Clicked");
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
}