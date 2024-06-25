#include "framework/MathUtility.h"
#include "player/PlayerSpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/FrontWiper.h"
#include "weapon/ThreeWayShooter.h"


namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& path)
		: Spaceship{ owningWorld, path },
		mMoveInput{},
		mSpeed{ 200.f },
		mShooter{ new BulletShooter {this, .5f, {50.f, 0.f}} },
		mInvulnerableTime{ 2.f },
		mIsInvulnerable{ true },
		mInvulnerableFlashInterval{ 0.5f },
		mInvulnerableFlashTimer{ 0.f },
		mInvulnerableFlashDir{ 1 }
	{
		SetTeamId(1);
		mShooter->SetCurrentLevel(4);
	}
	void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
	{
		if (mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
		{
			mShooter->IncrementLevel();
		}
		else
		{
			mShooter = std::move(newShooter);
		}
	}
	void PlayerSpaceship::Tick(float deltatime)
	{
		Spaceship::Tick(deltatime);
		HandleInput();
		ConsumeInput(deltatime);
		UpdateInvulnerable(deltatime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (mShooter)
		{
			mShooter->Shoot();
		}
	}
	void PlayerSpaceship::ApplyDamage(float amt)
	{
		if (!mIsInvulnerable)
		{
			Spaceship::ApplyDamage(amt);
		}
	}
	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();
		TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvunerable, mInvulnerableTime);
	}
	void PlayerSpaceship::UpdateInvulnerable(float deltatime)
	{
		if (!mIsInvulnerable) return;

		mInvulnerableFlashTimer += deltatime * mInvulnerableFlashDir;
		if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
		{
			mInvulnerableFlashDir *= -1;
		}

		GetSprite().setColor(LerpColor({ 255,255,255,64 }, { 255,255,255,128 }, mInvulnerableFlashTimer / mInvulnerableFlashInterval));
	}
	void PlayerSpaceship::StopInvunerable()
	{
		GetSprite().setColor({ 255,255,255,255 });
		mIsInvulnerable = false;
	}
	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(mMoveInput);
	}
	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		if (actorLocation.x < 0 && mMoveInput.x == -1)
		{
			mMoveInput.x = 0.f;
		}
		if (actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f)
		{
			mMoveInput.x = 0.f;
		}

		if (actorLocation.y < 0 && mMoveInput.y == -1)
		{
			mMoveInput.y = 0.f;
		}

		if (actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f)
		{
			mMoveInput.y = 0.f;
		}
	}
	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMoveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mMoveInput.y = 1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mMoveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMoveInput.x = 1.f;
		}

		ClampInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}

	}
	void PlayerSpaceship::ConsumeInput(float deltatime)
	{
		SetVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}
}

