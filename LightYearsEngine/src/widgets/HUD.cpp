#include "widgets/HUD.h"

namespace ly
{
	void HUD::NativeInit(sf::RenderWindow& windowRef)
	{
		if (!mAlreadInit)
		{
			mAlreadInit = true;
			Init(windowRef);
		}
	}
	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}
	HUD::HUD()
		: mAlreadInit{ false }
	{
	}
	void HUD::Init(sf::RenderWindow& windowRef)
	{
	}
}