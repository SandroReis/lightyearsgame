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
		void SetAssetRootDirectory(const std::string& directory);
		void SetMusicVolume(float vol);

		void IncreaseVol(float amt);
		void DecreaseVol(float amt);

		void PlaySound(const std::string& soundPath);
		void RemoveStoppedSounds();

	protected:
		SoundSystem();

	private:
		static unique<SoundSystem> soundSystem;
		sf::Music mCurrentMusic;
		std::string mRootDirectory;
		float mMusicVol;

		std::unordered_map<std::string, sf::SoundBuffer> mSoundBuffers;
		std::list<sf::Sound> mSounds;
		sf::Sound mCurrentSound;
		sf::Sound mLongshotSound;


	};
}