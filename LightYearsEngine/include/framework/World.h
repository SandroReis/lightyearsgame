#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <SFML/Graphics.hpp>
namespace ly
{
	class HUD;
	class Actor;
	class GameStage;
	class Application;
	class World : public Object
	{
	public:
		World(Application* owningApp);

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World();

		template<typename ActorType, typename... Args>
		weak<ActorType> SpawnActor(Args... args);

		sf::Vector2u GetWindowSize() const;
		void CleanCycle();
		void AddStage(const shared<GameStage>& newStage);

		template<typename HUDType, typename... Args>
		weak<HUD> SpawnHUD(Args... arg);
		bool DispatchEvent(const sf::Event& event);
	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		Application* mOwningApp;
		bool mBeganPlay;

		void RenderHUD(sf::RenderWindow& window);

		List<shared<Actor>> mActors;

		List<shared<Actor>> mPendingActors;

		List<shared<GameStage>> mGameStages;

		List<shared<GameStage>>::iterator mCurrentStage;

		shared<HUD> mHUD;


		virtual void InitGameStage();
		void NextGameStage();
		virtual void AllGameStageFinished();
		void StartStages();
	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...) };
		mPendingActors.push_back(newActor);
		return newActor;
	}
	template<typename HUDType, typename ...Args>
	inline weak<HUD> World::SpawnHUD(Args ...arg)
	{
		shared<HUDType> newHUD{ new HUDType(args...) };
		mHUD = newHUD;
		return newHUD;
	}
}