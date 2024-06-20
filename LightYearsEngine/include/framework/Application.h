#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
namespace ly
{
	class World;

	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned windowHeigth, const std::string& title, sf::Uint32 style);
		void Run();

		template<typename WordType>
		weak<WordType> LoadWorld();

		sf::Vector2u GetWindowSize() const;

		sf::RenderWindow& GetWindow() { return mWindow; }
		const sf::RenderWindow& GetWindow() const { return mWindow; };

	private:
		bool DispatchEvent(const sf::Event& event);
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow mWindow;
		float mTargetFramerate;
		sf::Clock mTickClock;

		shared<World> mCurrentWorld;
		sf::Clock mCleanCycleClock;
		float mCleanCycleIterval;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		mCurrentWorld = newWorld;
		mCurrentWorld->BeginPlayInternal();

		return newWorld;
	}
}