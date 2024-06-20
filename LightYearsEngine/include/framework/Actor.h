#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Delegate.h"
#include "framework/Object.h"

class b2Body;


namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		void BeginPlayInternal();
		void TickInternal(float deltatime);

		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLoc);
		void SetActorRotation(float newRot);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;
		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;
		sf::FloatRect GetActorGlobalBounds() const;

		sf::Vector2u GetWindowSize() const;

		World* GetWorld() { return mOwningWorld; };
		const World* GetWorld() const { return mOwningWorld; };
		bool IsActorOutOfWindowBounds(float allowance = 10.f) const;
		void SetEnablePhysics(bool enable);
		static uint8 GetNeutralTeamId() { return neutralTeamID; };
		sf::Sprite& GetSprite() { return mSprite; };
		void SetTeamId(uint8 teamID) { mTeamID = teamID; };
		uint8 GetTeamId() const { return mTeamID; };
		bool IsOtherHostile(Actor* other) const;

		const sf::Sprite& GetSprite() const { return mSprite; };

		Delegate<Actor*> onActorDestroy;


	public:
		virtual ~Actor();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);
		virtual void Destroy() override;
		virtual void ApplyDamage(float amt);
	private:
		void InitializePhysics();
		void UnitializePhysics();
		void UpdatePhysicsBodyTransform();

		void CenterPivot();
		World* mOwningWorld;
		bool mHasBeganlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;

		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;
		uint8 mTeamID;

		const static uint8 neutralTeamID = 255;
	};
}