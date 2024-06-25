#include "framework/Core.h"
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
		if (!mCurrentMusic.openFromFile(mRootDirectory + musicPath))
			return; // error

		mCurrentMusic.setVolume(mMusicVol);
		mCurrentMusic.setLoop(true);
		mCurrentMusic.play();
	}
	void SoundSystem::StopMusic()
	{
		mCurrentMusic.stop();
	}
	void SoundSystem::SetAssetRootDirectory(const std::string& directory)
	{
		mRootDirectory = directory;
	}
	void SoundSystem::SetMusicVolume(float vol)
	{
		mMusicVol = vol;
		mCurrentMusic.setVolume(mMusicVol);
	}
	void SoundSystem::IncreaseVol(float amt)
	{
		float cVol = mCurrentMusic.getVolume();
		mMusicVol = cVol + amt;
		if (cVol + amt > 100)
		{
			mMusicVol = 100;
		}
		mCurrentMusic.setVolume(mMusicVol);
	}

	void SoundSystem::DecreaseVol(float amt)
	{

		float cVol = mCurrentMusic.getVolume();
		mMusicVol = cVol - amt;
		if (cVol - amt < 0)
		{
			mMusicVol = 0;
		}
		mCurrentMusic.setVolume(mMusicVol);
	}
	SoundSystem::SoundSystem()
		: mCurrentMusic{},
		mMusicVol{ 10.f }
	{
	}
}