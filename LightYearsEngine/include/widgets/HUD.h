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
		bool HasInit() { return mAlreadyInit; }
		virtual bool HandleEvent(const sf::Event& evet);
		virtual void Tick(float deltatime);
	protected:
		HUD();

	private:
		virtual void Init(const sf::RenderWindow& windowRef);
		bool mAlreadyInit;
	};
}