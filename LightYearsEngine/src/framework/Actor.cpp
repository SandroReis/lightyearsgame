#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"
#include "framework/PhysicsSystem.h"
#include "framework/World.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningWorld{ owningWorld },
		mHasBeganlay{ false },
		mSprite{},
		mTexture{},
		mPhysicsBody{ nullptr },
		mPhysicsEnabled{ false },
		mTeamID{ 255 }
	{
		SetTexture(texturePath);
	}

	void Actor::SetTextureRepeated(bool repeated)
	{
		mTexture->setRepeated(repeated);
	}

	Actor::~Actor()
	{
		//LOG("Actor destroyed");
	}
	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganlay)
		{
			mHasBeganlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltatime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltatime);
		}
	}
	void Actor::BeginPlay()
	{

	}
	void Actor::Tick(float deltaTime)
	{


	}
	void Actor::SetTexture(const std::string& texturePath)
	{

		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{ textureWidth ,textureHeight } });
		CenterPivot();
	}
	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(mSprite);
	}
	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		mSprite.setPosition(newLoc);
		UpdatePhysicsBodyTransform();
	}
	void Actor::SetActorRotation(float newRot)
	{
		mSprite.setRotation(newRot);
		UpdatePhysicsBodyTransform();
	}
	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}
	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}
	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}
	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}
	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}
	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);

	}
	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}
	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}
	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
	bool Actor::IsActorOutOfWindowBounds(float allowance) const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPos = GetActorLocation();

		if (actorPos.x < -width - allowance)
		{
			return true;
		}

		if (actorPos.x > windowWidth + width + allowance)
		{
			return true;
		}

		if (actorPos.y < -height - allowance)
		{
			return true;
		}

		if (actorPos.y > windowHeight + height + allowance)
		{
			return true;
		}

		return false;


	}
	void Actor::SetEnablePhysics(bool enable)
	{
		mPhysicsEnabled = enable;
		if (mPhysicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UnitializePhysics();
		}
	}
	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (other == nullptr) return false;

		if (GetTeamId() == GetNeutralTeamId() || other->GetTeamId() == GetNeutralTeamId())
		{
			return false;
		}

		return GetTeamId() != other->GetTeamId();
	}
	void Actor::ApplyDamage(float amt)
	{
	}
	void Actor::InitializePhysics()
	{

		if (!mPhysicsBody)
		{
			mPhysicsBody = PhysicsSystem::Get().AddListener(this);
		}
	}
	void Actor::UnitializePhysics()
	{
		if (mPhysicsBody) {
			PhysicsSystem::Get().RemoveListener(mPhysicsBody);
			mPhysicsBody->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
			mPhysicsBody = nullptr;
		}

	}
	void Actor::UpdatePhysicsBodyTransform()
	{
		if (mPhysicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale };
			float rotation = DegreesToRadians(GetActorRotation());

			mPhysicsBody->SetTransform(pos, rotation);
		}
	}


	void Actor::OnActorBeginOverlap(Actor* other)
	{
	}
	void Actor::OnActorEndOverlap(Actor* other)
	{
	}
	void Actor::Destroy()
	{
		UnitializePhysics();
		onActorDestroy.Broadcast(this);
		Object::Destroy();
	}
}

