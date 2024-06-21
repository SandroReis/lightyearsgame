#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"
#include "framework/World.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned windowHeigth, const std::string& title, sf::Uint32 style)
		: mWindow{ sf::VideoMode(windowWidth,windowHeigth), title, style },
		mTargetFramerate{ 60.f },
		mTickClock{},
		mCurrentWorld{ nullptr },
		mCleanCycleClock{},
		mCleanCycleIterval{ 2.f }
	{
	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFramerate;
		while (mWindow.isOpen())
		{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					mWindow.close();
				}
			}

			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}


		}
	}
	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}
	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (mCurrentWorld)
		{
			mCurrentWorld->TickInternal(deltaTime);
		}


		TimerManager::Get().UpdateTimer(deltaTime);

		PhysicsSystem::Get().Step(deltaTime);

		if (mCleanCycleClock.getElapsedTime().asSeconds() > mCleanCycleIterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if (mCurrentWorld)
			{
				mCurrentWorld->CleanCycle();
			}
		}
	}
	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();


		mWindow.display();
	}
	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}
	void Application::Tick(float deltaTime)
	{

	}
}

