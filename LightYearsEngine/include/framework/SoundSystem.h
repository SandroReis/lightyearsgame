#pragma once
#include "framework/Core.h"
#include <SFML/Audio.hpp>

namespace ly
{
	class SoundSystem
	{
	public:
		static SoundSystem& Get();
		void PlayMusic(std::string musicPath);
		void StopMusic();

	protected:
		SoundSystem();


	private:
		static unique<SoundSystem> soundSystem;
		sf::Music mCurrentMusic;

	};
}