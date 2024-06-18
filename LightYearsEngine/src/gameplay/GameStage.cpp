#include "framework/Core.h"
#include "gameplay/GameStage.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: mWorld{ world }, mStageFinished{ false }
	{

	}
	void GameStage::StartStage()
	{
		LOG("stage started");
	}
	void GameStage::TickStage(float deltatime)
	{
	}
	void GameStage::FinishStage()
	{
		mStageFinished = true;
		StageFinished();
		onStageFinished.Broadcast();
	}
	void GameStage::StageFinished()
	{
		LOG("stage finished");
	}
}