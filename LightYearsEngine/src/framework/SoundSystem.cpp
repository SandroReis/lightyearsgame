#include "framework/SoundSystem.h"

namespace ly
{
	unique<SoundSystem> SoundSystem::soundSystem{ nullptr };

	SoundSystem& SoundSystem::Get()
	{
		if (!soundSystem)
		{
			soundSystem = std::move(unique<SoundSystem>{new SoundSystem});
		}

		return *soundSystem;
	}
	void SoundSystem::PlayMusic(std::string musicPath)
	{
		if (!mCurrentMusic.openFromFile(musicPath))
			return; // error

		mCurrentMusic.setLoop(true);
		mCurrentMusic.play();
	}
	void SoundSystem::StopMusic()
	{
		mCurrentMusic.stop();
	}
	SoundSystem::SoundSystem()
		: mCurrentMusic{}
	{
	}
}