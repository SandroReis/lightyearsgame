#pragma once
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;

		void NativeInit(const sf::RenderWindow& windowRef);

		bool HasInit() { return mAlreadInit; };
		virtual bool HandleEvent(const sf::Event& event);
	protected:
		HUD();


	private:
		virtual void Init(sf::RenderWindow& windowRef);
		bool mAlreadInit;
	};
}