#include "framework/Application.h"
#include "framework/BackdropActor.h"
#include "level/GameLevelOne.h"
#include "level/MainMenuLevel.h"
#include "widgets/MainMenuHUD.h"

namespace ly
{
	MainMenuLevel::MainMenuLevel(Application* owningApplication)
		: World{ owningApplication }
	{
		mMainMenuHUD = SpawnHUD<MainMenuHUD>();
	}
	void MainMenuLevel::BeginPlay()
	{
		mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
		mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);

		SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");

	}
	void MainMenuLevel::StartGame()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
	}
	void MainMenuLevel::QuitGame()
	{
		GetApplication()->QuitApplication();

	}
}