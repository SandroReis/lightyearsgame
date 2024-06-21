#include "widgets/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFramerateText{ "Frame rate:" }
	{
		mFramerateText.SetTextSize(24);
	}
	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFramerateText.NativeDraw(windowRef);
	}
	void GameplayHUD::Tick(float deltatime)
	{
		int frameRate = int(1 / deltatime);
		std::string framerateStr = "Frame rate: " + std::to_string(frameRate);
		mFramerateText.SetString(framerateStr);
	}
}