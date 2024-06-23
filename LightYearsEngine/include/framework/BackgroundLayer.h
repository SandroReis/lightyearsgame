#pragma once
#include "framework/Actor.h"

namespace ly
{
	class BackgroundLayer : public Actor
	{
	public:
		BackgroundLayer(World* owningWorld,
			const List<std::string>& assetPaths = {},
			const sf::Vector2f& minVel = sf::Vector2f{ 0.f, 50.f },
			const sf::Vector2f& maxVel = sf::Vector2f{ 0.f, 200.f },
			float sizeMin = 1.f,
			float sizeMax = 2.f,
			int spriteCount = 20,
			const sf::Color& colorTint = sf::Color{ 180,180,200,225 }

		);


		void SetAssets(const List<std::string>& assetPaths);
		void SetColorTint(const sf::Color& color);
		void SetSpriteCount(int newCount);
		virtual void Render(sf::RenderWindow& window) override;
		virtual void Tick(float deltatime) override;
		void SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max);
		void SetSizes(float min, float max);

	private:
		bool IsSpriteOffScreen(sf::Sprite& sprite) const;
		void RefreshSprites();
		void RandomSpriteTexture(sf::Sprite& sprite);
		void RandomSpriteTransform(sf::Sprite& sprite, bool randomY = false);
		void RandomSpritePosition(sf::Sprite& sprite, bool randomY);
		void RandomSpriteRotation(sf::Sprite& sprite);
		void RandomSpriteSize(sf::Sprite& sprite);


		shared<sf::Texture> GetRandomTexture() const;

		sf::Vector2f mMinVelocity;
		sf::Vector2f mMaxVelocity;
		float mSizeMin;
		float mSizeMax;
		int mSpriteCount;
		sf::Color mTintColor;

		List<sf::Sprite> mSprites;
		List<shared<sf::Texture>> mTextures;
		List<sf::Vector2f> mVelocities;
	};
}